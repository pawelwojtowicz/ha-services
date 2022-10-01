#pragma once
#include <flite/flite.h>
#include <memory>
namespace SpeakingAgent
{
class CTTS
{
public:
  CTTS();
  virtual ~CTTS();

  bool Initialize();
  void Shutdown();

  bool Say( const std::string& phrase);
private:
  std::unique_ptr<cst_voice> m_pFlite;
}

}