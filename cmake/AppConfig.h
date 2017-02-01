#ifndef __JUCE_APPCONFIG_@project_id@__
#define __JUCE_APPCONFIG_@project_id@__

//==============================================================================
@module_available_defines@
//==============================================================================
#ifndef    JUCE_STANDALONE_APPLICATION
 #ifdef JucePlugin_Build_Standalone
  #define  JUCE_STANDALONE_APPLICATION JucePlugin_Build_Standalone
 #else
  #define  JUCE_STANDALONE_APPLICATION @is_standalone_application@
 #endif
#endif

#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED 1

@config_flags_defines@
#endif  // __JUCE_APPCONFIG_@project_id@__
