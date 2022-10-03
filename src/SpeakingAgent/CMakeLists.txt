add_executable( speakingAgent CSpeakingAgent.cpp CSpeakingAgent.h CTTS.cpp CTTS.h)

target_link_libraries( speakingAgent global runtime mosquittopp flite_cmu_us_kal flite_cmu_us_slt flite_cmu_us_awb flite_cmu_us_rms flite_usenglish flite_cmulex flite)
install( TARGETS speakingAgent RUNTIME DESTINATION bin )
