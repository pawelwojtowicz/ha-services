#pragma once
#include <set>
#include <vector>
#include <string>

namespace oFonoIntegration
{

class CModemContext
{
public:
  CModemContext();
  CModemContext( const CModemContext& ctx );

  CModemContext& operator=(const CModemContext& ctx) = default;
  virtual ~CModemContext();

  void SetDBUSModemPath( const std::string& modemPath ) { m_dbusModemPath = modemPath; };
  void SetPowered( bool powered ) { m_powered = powered; } ;
  void SetOnline( bool online ) {  m_online = online; };
  void AddInterface( const std::string& interfaceName);
  void SetSystemPath( const std::string& sytemPath ) { m_systemPath = sytemPath; };

  const std::string& GetDBUSModemPath() const { return m_dbusModemPath; };
  bool IsPowered() const { return m_powered; };
  bool IsConnected() const { return m_online; };
  bool IsSMSServiceActive() const;
  const std::string& GetSystemPath() const { return m_systemPath; };

  void ToString() const;

private:
  std::string m_dbusModemPath;
  std::set<std::string> m_interfaces;
  bool m_online;
  bool m_powered;
  std::string m_systemPath;
};

using tModemList = std::vector<CModemContext>;
}