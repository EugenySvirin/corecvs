#ifndef COPTER_H_
#define COPTER_H_
/**
 * \file copter.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from copter.xml
 */

#include "core/reflection/reflection.h"
#include "core/reflection/defaultSetter.h"
#include "core/reflection/printerVisitor.h"

/*
 *  Embed includes.
 */
/*
 *  Additional includes for Composite Types.
 */

// using namespace corecvs;

/*
 *  Additional includes for Pointer Types.
 */

// namespace corecvs {
// }
/*
 *  Additional includes for enum section.
 */

/**
 * \brief Copter Parameters 
 * Copter Parameters 
 **/
class Copter : public corecvs::BaseReflection<Copter>
{
public:
    enum FieldId {
        PROCESSING_ID,
        FRAMESIZE_ID,
        INVERTED_ID,
        P_PITCH_ID,
        I_PITCH_ID,
        D_PITCH_ID,
        P_ROLL_ID,
        I_ROLL_ID,
        D_ROLL_ID,
        P_YAW_ID,
        I_YAW_ID,
        D_YAW_ID,
        COPTER_FIELD_ID_NUM
    };

    /** Section with variables */

    /** 
     * \brief processing 
     * processing 
     */
    bool mProcessing;

    /** 
     * \brief frameSize 
     * frameSize 
     */
    double mFrameSize;

    /** 
     * \brief inverted 
     * inverted 
     */
    bool mInverted;

    /** 
     * \brief P Pitch 
     * P Pitch 
     */
    double mPPitch;

    /** 
     * \brief I Pitch 
     * I Pitch 
     */
    double mIPitch;

    /** 
     * \brief D Pitch 
     * D Pitch 
     */
    double mDPitch;

    /** 
     * \brief P Roll 
     * P Roll 
     */
    double mPRoll;

    /** 
     * \brief I Roll 
     * I Roll 
     */
    double mIRoll;

    /** 
     * \brief D Roll 
     * D Roll 
     */
    double mDRoll;

    /** 
     * \brief P Yaw 
     * P Yaw 
     */
    double mPYaw;

    /** 
     * \brief I Yaw 
     * I Yaw 
     */
    double mIYaw;

    /** 
     * \brief D Yaw 
     * D Yaw 
     */
    double mDYaw;

    /** Static fields init function, this is used for "dynamic" field initialization */ 
    static int staticInit(corecvs::Reflection *toFill);

    static int relinkCompositeFields();

    /** Section with getters */
    const void *getPtrById(int fieldId) const
    {
        return (const unsigned char *)(this) + fields()[fieldId]->offset;
    }
    bool processing() const
    {
        return mProcessing;
    }

    double frameSize() const
    {
        return mFrameSize;
    }

    bool inverted() const
    {
        return mInverted;
    }

    double pPitch() const
    {
        return mPPitch;
    }

    double iPitch() const
    {
        return mIPitch;
    }

    double dPitch() const
    {
        return mDPitch;
    }

    double pRoll() const
    {
        return mPRoll;
    }

    double iRoll() const
    {
        return mIRoll;
    }

    double dRoll() const
    {
        return mDRoll;
    }

    double pYaw() const
    {
        return mPYaw;
    }

    double iYaw() const
    {
        return mIYaw;
    }

    double dYaw() const
    {
        return mDYaw;
    }

    /* Section with setters */
    void setProcessing(bool processing)
    {
        mProcessing = processing;
    }

    void setFrameSize(double frameSize)
    {
        mFrameSize = frameSize;
    }

    void setInverted(bool inverted)
    {
        mInverted = inverted;
    }

    void setPPitch(double pPitch)
    {
        mPPitch = pPitch;
    }

    void setIPitch(double iPitch)
    {
        mIPitch = iPitch;
    }

    void setDPitch(double dPitch)
    {
        mDPitch = dPitch;
    }

    void setPRoll(double pRoll)
    {
        mPRoll = pRoll;
    }

    void setIRoll(double iRoll)
    {
        mIRoll = iRoll;
    }

    void setDRoll(double dRoll)
    {
        mDRoll = dRoll;
    }

    void setPYaw(double pYaw)
    {
        mPYaw = pYaw;
    }

    void setIYaw(double iYaw)
    {
        mIYaw = iYaw;
    }

    void setDYaw(double dYaw)
    {
        mDYaw = dYaw;
    }

    /* Section with embedded classes */
    /* visitor pattern - http://en.wikipedia.org/wiki/Visitor_pattern */
template<class VisitorType>
    void accept(VisitorType &visitor)
    {
        visitor.visit(mProcessing,                static_cast<const corecvs::BoolField *>(fields()[PROCESSING_ID]));
        visitor.visit(mFrameSize,                 static_cast<const corecvs::DoubleField *>(fields()[FRAMESIZE_ID]));
        visitor.visit(mInverted,                  static_cast<const corecvs::BoolField *>(fields()[INVERTED_ID]));
        visitor.visit(mPPitch,                    static_cast<const corecvs::DoubleField *>(fields()[P_PITCH_ID]));
        visitor.visit(mIPitch,                    static_cast<const corecvs::DoubleField *>(fields()[I_PITCH_ID]));
        visitor.visit(mDPitch,                    static_cast<const corecvs::DoubleField *>(fields()[D_PITCH_ID]));
        visitor.visit(mPRoll,                     static_cast<const corecvs::DoubleField *>(fields()[P_ROLL_ID]));
        visitor.visit(mIRoll,                     static_cast<const corecvs::DoubleField *>(fields()[I_ROLL_ID]));
        visitor.visit(mDRoll,                     static_cast<const corecvs::DoubleField *>(fields()[D_ROLL_ID]));
        visitor.visit(mPYaw,                      static_cast<const corecvs::DoubleField *>(fields()[P_YAW_ID]));
        visitor.visit(mIYaw,                      static_cast<const corecvs::DoubleField *>(fields()[I_YAW_ID]));
        visitor.visit(mDYaw,                      static_cast<const corecvs::DoubleField *>(fields()[D_YAW_ID]));
    }

    Copter()
    {
        corecvs::DefaultSetter setter;
        accept(setter);
    }

    Copter(
          bool processing
        , double frameSize
        , bool inverted
        , double pPitch
        , double iPitch
        , double dPitch
        , double pRoll
        , double iRoll
        , double dRoll
        , double pYaw
        , double iYaw
        , double dYaw
    )
    {
        mProcessing = processing;
        mFrameSize = frameSize;
        mInverted = inverted;
        mPPitch = pPitch;
        mIPitch = iPitch;
        mDPitch = dPitch;
        mPRoll = pRoll;
        mIRoll = iRoll;
        mDRoll = dRoll;
        mPYaw = pYaw;
        mIYaw = iYaw;
        mDYaw = dYaw;
    }

    bool operator ==(const Copter &other) const 
    {
        if ( !(this->mProcessing == other.mProcessing)) return false;
        if ( !(this->mFrameSize == other.mFrameSize)) return false;
        if ( !(this->mInverted == other.mInverted)) return false;
        if ( !(this->mPPitch == other.mPPitch)) return false;
        if ( !(this->mIPitch == other.mIPitch)) return false;
        if ( !(this->mDPitch == other.mDPitch)) return false;
        if ( !(this->mPRoll == other.mPRoll)) return false;
        if ( !(this->mIRoll == other.mIRoll)) return false;
        if ( !(this->mDRoll == other.mDRoll)) return false;
        if ( !(this->mPYaw == other.mPYaw)) return false;
        if ( !(this->mIYaw == other.mIYaw)) return false;
        if ( !(this->mDYaw == other.mDYaw)) return false;
        return true;
    }
    friend std::ostream& operator << (std::ostream &out, Copter &toSave)
    {
        corecvs::PrinterVisitor printer(out);
        toSave.accept<corecvs::PrinterVisitor>(printer);
        return out;
    }

    void print ()
    {
        std::cout << *this;
    }
};
#endif  //COPTER_H_