target_sources(corecvs
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/flatPatternCalibrator.h    
        ${CMAKE_CURRENT_LIST_DIR}/calibrationLocation.h             
        ${CMAKE_CURRENT_LIST_DIR}/cameraConstraints.h        
        ${CMAKE_CURRENT_LIST_DIR}/calibrationDrawHelpers.h          
        ${CMAKE_CURRENT_LIST_DIR}/cameraModel.h              
        ${CMAKE_CURRENT_LIST_DIR}/projection/projectionModels.h         
        ${CMAKE_CURRENT_LIST_DIR}/projection/pinholeCameraIntrinsics.h  
        ${CMAKE_CURRENT_LIST_DIR}/projection/equidistantProjection.h    
        ${CMAKE_CURRENT_LIST_DIR}/projection/equisolidAngleProjection.h 
        ${CMAKE_CURRENT_LIST_DIR}/projection/stereographicProjection.h
        ${CMAKE_CURRENT_LIST_DIR}/projection/projectionFactory.h
        ${CMAKE_CURRENT_LIST_DIR}/ilFormat.h
        ${CMAKE_CURRENT_LIST_DIR}/projection/omnidirectionalProjection.h


    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/calibrationLocation.cpp      
        ${CMAKE_CURRENT_LIST_DIR}/flatPatternCalibrator.cpp    
        ${CMAKE_CURRENT_LIST_DIR}/cameraConstraints.cpp        
        ${CMAKE_CURRENT_LIST_DIR}/calibrationDrawHelpers.cpp   
        ${CMAKE_CURRENT_LIST_DIR}/cameraModel.cpp              
        ${CMAKE_CURRENT_LIST_DIR}/projection/projectionModels.cpp         
        ${CMAKE_CURRENT_LIST_DIR}/projection/pinholeCameraIntrinsics.cpp  
        ${CMAKE_CURRENT_LIST_DIR}/projection/equidistantProjection.cpp    
        ${CMAKE_CURRENT_LIST_DIR}/projection/equisolidAngleProjection.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/projection/stereographicProjection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/projection/projectionFactory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ilFormat.cpp
        ${CMAKE_CURRENT_LIST_DIR}/projection/omnidirectionalProjection.cpp

    )
