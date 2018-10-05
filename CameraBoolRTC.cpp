#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/DataOutPort.h>
#include <rtm/Manager.h>
#include <rtm/CorbaPort.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

using namespace RTC;
using namespace std;

class CameraBoolRTC : public RTC::DataFlowComponentBase
{
public:
    CameraBoolRTC(RTC::Manager* manager);
    ~CameraBoolRTC();

    virtual RTC::ReturnCode_t onInitialize();
    virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
    virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
    virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

protected:
    int m_Cam1;
    int m_Cam2;
    int m_Cam3;
    int m_Cam4;

    RTC::TimedBoolean m_CameraBool1;
    /*!
    */
    OutPort<RTC::TimedBoolean> m_CameraBool1Out;
    RTC::TimedBoolean m_CameraBool2;
    /*!
    */
    OutPort<RTC::TimedBoolean> m_CameraBool2Out;
    RTC::TimedBoolean m_CameraBool3;
    /*!
    */
    OutPort<RTC::TimedBoolean> m_CameraBool3Out;
    RTC::TimedBoolean m_CameraBool4;
    /*!
    */
    OutPort<RTC::TimedBoolean> m_CameraBool4Out;

private:

};


CameraBoolRTC::CameraBoolRTC(RTC::Manager* manager)
    : RTC::DataFlowComponentBase(manager),
    m_CameraBool1Out("CameraBool1", m_CameraBool1),
    m_CameraBool2Out("CameraBool2", m_CameraBool2),
    m_CameraBool3Out("CameraBool3", m_CameraBool3),
    m_CameraBool4Out("CameraBool4", m_CameraBool4)
{
}


CameraBoolRTC::~CameraBoolRTC()
{
}


RTC::ReturnCode_t CameraBoolRTC::onInitialize()
{
  // Set OutPort buffer
  addOutPort("CameraBool1", m_CameraBool1Out);
  addOutPort("CameraBool2", m_CameraBool2Out);
  addOutPort("CameraBool3", m_CameraBool3Out);
  addOutPort("CameraBool4", m_CameraBool4Out);
  
  bindParameter("Cam1", m_Cam1, "1");
  bindParameter("Cam2", m_Cam2, "0");
  bindParameter("Cam3", m_Cam3, "0");
  bindParameter("Cam4", m_Cam4, "0");
  // </rtc-template>
  
    return RTC::RTC_OK;
}


RTC::ReturnCode_t CameraBoolRTC::onActivated(RTC::UniqueId ec_id)
{

        return RTC::RTC_OK;
    
}


RTC::ReturnCode_t CameraBoolRTC::onDeactivated(RTC::UniqueId ec_id)
{

    return RTC::RTC_OK;
}



RTC::ReturnCode_t CameraBoolRTC::onExecute(RTC::UniqueId ec_id)
{
    m_CameraBool1.data = m_Cam1;
    m_CameraBool2.data = m_Cam2;
    m_CameraBool3.data = m_Cam3;
    m_CameraBool4.data = m_Cam4;
    
    m_CameraBool1Out.write();
    m_CameraBool2Out.write();
    m_CameraBool3Out.write();
    m_CameraBool4Out.write();

    return RTC::RTC_OK;
}


extern "C"
{
    DLL_EXPORT void CameraBoolRTCInit(RTC::Manager* manager)
    {
        static const char* spec[] = {
                "implementation_id", "CameraBoolRTC",
                "type_name",         "CameraBoolRTC",
                "description",       "On Off function for camera",
                "version",           "1.0.0",
                "vendor",            "Fumiaki Abe",
                "category",          "Category",
                "activity_type",     "PERIODIC",
                "kind",              "DataFlowComponent",
                "max_instance",      "1",
                "language",          "C++",
                "lang_type",         "compile",
                // Configuration variables
                "conf.default.Cam1", "1",
                "conf.default.Cam2", "0",
                "conf.default.Cam3", "0",
                "conf.default.Cam4", "0",
            
                // Widget
                "conf.__widget__.Cam1", "radio",
                "conf.__widget__.Cam2", "radio",
                "conf.__widget__.Cam3", "radio",
                "conf.__widget__.Cam4", "radio",
                // Constraints
                "conf.__constraints__.Cam1", "(0,1)",
                "conf.__constraints__.Cam2", "(0,1)",
                "conf.__constraints__.Cam3", "(0,1)",
                "conf.__constraints__.Cam4", "(0,1)",
            
                "conf.__type__.Cam1", "int",
                "conf.__type__.Cam2", "int",
                "conf.__type__.Cam3", "int",
                "conf.__type__.Cam4", "int",
            
                ""
        };
        coil::Properties profile(spec);
        
        manager->registerFactory(
            profile, RTC::Create<CameraBoolRTC>, RTC::Delete<CameraBoolRTC>);
    }
};
