#include "CTTS.h"

extern "C" 
{
cst_voice *register_cmu_us_kal(const char*);				// mans voice
cst_voice *register_cmu_us_awb(const char *voxdir); // mans voice
cst_voice *register_cmu_us_rms(const char *voxdir);	// slappy mans voice
cst_voice *register_cmu_us_slt(const char *voxdir); // womans voice
}

namespace SpeakingAgent
{
CTTS::CTTS()
{
}
  
CTTS::~CTTS()
{
} 

bool CTTS::Initialize()
{
	flite_init();
	m_pFlite.reset(register_cmu_us_slt(NULL));
	return ( m_pFlite );

}

void CTTS::Shutdown()
{

}

bool CTTS::Say( const std::string& phrase)
{
	float phraseLength(0);
	
	if ( m_pFlite )
	{
		phraseLength = flite_text_to_speech( text.c_str() , m_pFlite.get() , "play" );
	}

	return ( 0 != phraseLength );
}

}