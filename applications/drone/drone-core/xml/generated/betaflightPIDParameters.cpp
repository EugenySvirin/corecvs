/**
 * \file betaflightPIDParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from physics.xml
 */

#include <vector>
#include <stddef.h>
#include "betaflightPIDParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
#if 0
template<>
Reflection BaseReflection<BetaflightPIDParameters>::reflection = Reflection();
template<>
int BaseReflection<BetaflightPIDParameters>::dummy = BetaflightPIDParameters::staticInit();
#endif
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN


using namespace corecvs;

int BetaflightPIDParameters::staticInit(corecvs::Reflection *toFill)
{
    if (toFill == NULL || toFill->objectSize != 0) {
        SYNC_PRINT(("staticInit(): Contract Violation in <BetaflightPIDParameters>\n"));
         return -1;
    }

    toFill->name = ReflectionNaming(
        "Betaflight PID Parameters",
        "Betaflight PID Parameters",
        ""
    );

     toFill->objectSize = sizeof(BetaflightPIDParameters);
     

    CompositeField* field0 = new CompositeField
        (
          BetaflightPIDParameters::ROLL_PID_ID,
          offsetof(BetaflightPIDParameters, mRollPID),
          "Roll PID",
          "PIDParameters",
          "Roll PID",
          "Roll PID",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("PID Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field0->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass PID Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field0);
    /*  */ 
    CompositeField* field1 = new CompositeField
        (
          BetaflightPIDParameters::PITCH_PID_ID,
          offsetof(BetaflightPIDParameters, mPitchPID),
          "Pitch PID",
          "PIDParameters",
          "Pitch PID",
          "Pitch PID",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("PID Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field1->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass PID Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field1);
    /*  */ 
    CompositeField* field2 = new CompositeField
        (
          BetaflightPIDParameters::YAW_PID_ID,
          offsetof(BetaflightPIDParameters, mYawPID),
          "Yaw PID",
          "PIDParameters",
          "Yaw PID",
          "Yaw PID",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("PID Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field2->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass PID Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field2);
    /*  */ 
    CompositeField* field3 = new CompositeField
        (
          BetaflightPIDParameters::ROLL_RATE_ID,
          offsetof(BetaflightPIDParameters, mRollRate),
          "Roll Rate",
          "RateParameters",
          "Roll Rate",
          "Roll Rate",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Rate Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field3->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass Rate Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field3);
    /*  */ 
    CompositeField* field4 = new CompositeField
        (
          BetaflightPIDParameters::PITCH_RATE_ID,
          offsetof(BetaflightPIDParameters, mPitchRate),
          "Pitch Rate",
          "RateParameters",
          "Pitch Rate",
          "Pitch Rate",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Rate Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field4->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass Rate Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field4);
    /*  */ 
    CompositeField* field5 = new CompositeField
        (
          BetaflightPIDParameters::YAW_RATE_ID,
          offsetof(BetaflightPIDParameters, mYawRate),
          "Yaw Rate",
          "RateParameters",
          "Yaw Rate",
          "Yaw Rate",
           NULL
        );
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Rate Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             field5->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass Rate Parameters can't be linked\n");
        }
    }
    toFill->fields.push_back(field5);
    /*  */ 
    ReflectionDirectory &directory = *ReflectionDirectoryHolder::getReflectionDirectory();
    directory[std::string("Betaflight PID Parameters")]= toFill;
   return 0;
}
int BetaflightPIDParameters::relinkCompositeFields()
{
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("PID Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[0]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass PID Parameters can't be linked\n");
        }
    }
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("PID Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[1]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass PID Parameters can't be linked\n");
        }
    }
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("PID Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[2]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass PID Parameters can't be linked\n");
        }
    }
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Rate Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[3]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass Rate Parameters can't be linked\n");
        }
    }
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Rate Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[4]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass Rate Parameters can't be linked\n");
        }
    }
    {
        ReflectionDirectory* directory = ReflectionDirectoryHolder::getReflectionDirectory();
        std::string name("Rate Parameters");
        ReflectionDirectory::iterator it = directory->find(name);
        if(it != directory->end()) {
             const CompositeField* field = static_cast<const CompositeField*>(getReflection()->fields[5]);
             const_cast<CompositeField*>(field)->reflection = it->second;
        } else {
             printf("Reflection BetaflightPIDParameters to the subclass Rate Parameters can't be linked\n");
        }
    }
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


