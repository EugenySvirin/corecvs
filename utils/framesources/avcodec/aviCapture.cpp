/**
 * \brief Capture video stream from avi file using avcodec library
 */
#include <QtCore/QRegExp>
#include <QtCore/QString>

#include "aviCapture.h"


bool AviCapture::avCodecInited = false;

AviCapture::AviCapture(QString const &params)
    : /*AbstractFileCapture(params),*/
       mName(params.toStdString())
     , mFormatContext(NULL)
     , mCodecContext(NULL)
     , mCodec(NULL)
     , mFrame(NULL)
     , count(1)
{
    SYNC_PRINT(("AviCapture::AviCapture(%s): called\n", params.toAscii().constData()));
    if (!avCodecInited)
    {
        SYNC_PRINT(("Registering the codecs...\n"));
        av_register_all();
        avCodecInited = true;
    }

    SYNC_PRINT(("AviCapture::AviCapture(): exited\n"));
}

ImageCaptureInterface::CapErrorCode AviCapture::initCapture()
{
    SYNC_PRINT(("AviCapture::initCapture(): called\n"));

    int res;
    res = avformat_open_input(&mFormatContext, mName.c_str(), NULL, NULL);
    if (res < 0) {
        SYNC_PRINT(("AviCapture::initCapture(): failed to open file"));
        return ImageCaptureInterface::FAILURE;
    }

    res = avformat_find_stream_info(mFormatContext, NULL);
    if (res < 0) {
        SYNC_PRINT(("AviCapture::initCapture(): Unable to find stream info\n"));
        return ImageCaptureInterface::FAILURE;
    }

    SYNC_PRINT(("File seem to have %d streams\n", mFormatContext->nb_streams));

    // Dump information about file onto standard error
    av_dump_format(mFormatContext, 0, mName.c_str(), 0);

    // Find the first video stream
    for (mVideoStream = 0; mVideoStream < mFormatContext->nb_streams; mVideoStream++) {
        if (mFormatContext->streams[mVideoStream]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            break;
        }
    }

    if (mVideoStream == mFormatContext->nb_streams) {
        SYNC_PRINT(("AviCapture::initCapture(): Unable to find video stream among %d streams\n", mFormatContext->nb_streams));
        return ImageCaptureInterface::FAILURE;
    }

    SYNC_PRINT(("AviCapture::initCapture(): Video Stream found\n"));
    mCodecContext = mFormatContext->streams[mVideoStream]->codec;
    mCodec = avcodec_find_decoder(mCodecContext->codec_id);
    res = avcodec_open2(mCodecContext, mCodec, NULL);
    if (res < 0) {
        SYNC_PRINT(("AviCapture::initCapture(): Unable to open codec\n"));
        return ImageCaptureInterface::FAILURE;
    }
    SYNC_PRINT(("AviCapture::initCapture(): Video codec found\n"));

    mFrame = avcodec_alloc_frame();

    SYNC_PRINT(("AviCapture::initCapture(): exited\n"));
    return ImageCaptureInterface::SUCCESS_1CAM;
}

ImageCaptureInterface::FramePair AviCapture::getFrame()
{
    SYNC_PRINT(("AviCapture::getFrame(): called\n"));
    //mProtectFrame.lock();
        FramePair result(NULL, NULL);
        int res;
        while ( (res = av_read_frame(mFormatContext, &mPacket)) >= 0)
        {
            if (mPacket.stream_index == mVideoStream)
            {
                int frame_finished;
                avcodec_decode_video2(mCodecContext, mFrame, &frame_finished, &mPacket);

                if (frame_finished) {
                    SYNC_PRINT(("AviCapture::getFrame(): Frame ready\n"));
                    break;
                }

                // Free the packet that was allocated by av_read_frame
                av_free_packet(&mPacket);
            }
        }

        if (res >= 0)
        {
            if (mFrame->format != AV_PIX_FMT_YUV420P)
            {
                SYNC_PRINT(("Not supported format"));
                return result;
            }

            result.rgbBufferLeft = new RGB24Buffer(mFrame->height, mFrame->width);
            result.bufferLeft    = new G12Buffer  (mFrame->height, mFrame->width);
            for (int i = 0; i < mFrame->height; i++)
            {
                for (int j = 0; j < mFrame->width; j++)
                {
                    uint8_t y = (mFrame->data[0])[i * mFrame->linesize[0] + j];

                    uint8_t u = 128; (mFrame->data[1])[(i / 2) * mFrame->linesize[1] + (j / 2)];
                    uint8_t v = 128; (mFrame->data[2])[(i / 2) * mFrame->linesize[2] + (j / 2)];

                    result.rgbBufferLeft->element(i,j) = RGBColor::FromYUV(y,u,v);
                    result.bufferLeft   ->element(i,j) = (int)y << 4;
                }
            }

            result.rgbBufferRight = new RGB24Buffer(result.rgbBufferLeft);
            result.bufferRight = new G12Buffer(result.bufferLeft);
        }


        result.leftTimeStamp  = count * 10;
        result.rightTimeStamp = count * 10;

    //mProtectFrame.unlock();


    count++;
    frame_data_t frameData;
    frameData.timestamp = (count * 10);
    notifyAboutNewFrame(frameData);
    //count++;

    return result;
}

ImageCaptureInterface::CapErrorCode AviCapture::startCapture()
{
//  return ImageCaptureInterface::CapSuccess1Cam;
    SYNC_PRINT(("AviCapture::startCapture(): called\n"));
    frame_data_t frameData;
    frameData.timestamp = (count * 10);

    SYNC_PRINT(("AviCapture::startCapture(): sending notification\n"));
    notifyAboutNewFrame(frameData);
    count++;

    SYNC_PRINT(("AviCapture::startCapture(): exited\n"));
    return ImageCaptureInterface::SUCCESS;
}

AviCapture::~AviCapture()
{
    SYNC_PRINT(("AviCapture::~AviCapture(): called\n"));

    av_free(mFrame);
    avcodec_close(mCodecContext);
    avformat_close_input(&mFormatContext);

    SYNC_PRINT(("AviCapture::~AviCapture(): exited\n"));
}
