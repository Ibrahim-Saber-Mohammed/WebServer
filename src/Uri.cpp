#include <Uri/Uri.hpp>
#include <iostream>
namespace Uri
{
	struct Uri::Impl
	{
		/**
		 * This is the "scheme" element of the URI
		 */
		std::string scheme_;
		/**
		 * This is the "host" element of the URI
		 */
		std::string host_;
		/**
			* This is the "path" element of the URI.
			  as a sequence of path segemnts.
		*/
		std::vector<std::string> path_;
		/**
		 * This is the "authority" element of the URI
		 */
		std::string authority_;
		/**
		 * This is the "hasPort_"
		 * An Indication whether or not the URI has a port number.
		 */
		bool hasPort_{false};
		/**
		 * This is the "port" element of the URI
		 */
		uint16_t port_{0};
		/**
		 * This is the "query" element of the URI
		 */
		std::string query_;
		/**
		 * This is the "fregment" element of the URI
		 */
		std::string fragment_;
		/**
		 * This is the "userInfo" element of the URI
		 */
		std::string userInfo_;

		/*bool UriHasPort()
		{

		}
		bool ParsePortNumber(std::string& input)
		{

		}*/
	};

	Uri::Uri() : impl_(new Impl) {}
	Uri::~Uri() = default;

	bool Uri::ParseFromString(const std::string &UriString)
	{
		// TODO: Refactor this method
		std::string rest{};
		const auto l_SchemeEnd = UriString.find(':');
		if (l_SchemeEnd == std::string::npos)
		{
			impl_->scheme_.clear();
			rest = UriString;
		}
		else
		{
			impl_->scheme_ = UriString.substr(0, l_SchemeEnd);
			rest = UriString.substr(l_SchemeEnd + 1);
		}
		// Parsing the Authority, host and port
		
		if (rest.substr(0, 2) == "//")
		{
			// paring the Fragment
			auto l_FragmentDelimiter = rest.find('#', 2);
			if(l_FragmentDelimiter == std::string::npos)
			{
				impl_->fragment_.clear();
				l_FragmentDelimiter = rest.length();
			}
			else{
				impl_->fragment_ = rest.substr(l_FragmentDelimiter + 1);
			}
			rest = rest.substr(0, l_FragmentDelimiter);
			// paring the Query
			auto l_QueryDelimiter = rest.find('?', 2);
			if(l_QueryDelimiter == std::string::npos)
			{
				impl_->query_.clear();
				l_QueryDelimiter = rest.length();
			}
			else{
				impl_->query_ = rest.substr(l_QueryDelimiter + 1, rest.length());
			}

			rest = rest.substr(0, l_QueryDelimiter);
			
			impl_->port_ = 0;
			impl_->hasPort_ = false;
			auto l_userInfoDelimiter = rest.find('@');
			if (l_userInfoDelimiter == std::string::npos)
			{
				l_userInfoDelimiter = rest.length();
				impl_->userInfo_.clear();
			}else{
				impl_->userInfo_ = rest.substr(2, l_userInfoDelimiter-2);
				rest.erase(2,l_userInfoDelimiter - 1);
			}
			// Parsing the authority host and port number
			auto l_AuthorityEnd = rest.find('/', 2);
			// URI = "https://www.google.com"
			if (l_AuthorityEnd == std::string::npos)
			{
				l_AuthorityEnd = rest.length();
			}
			// URI = "https://www.google.com/online"
			impl_->authority_ = rest.substr(2, l_AuthorityEnd - 2);
						// Check for the userInfo in the URI			
			
			// URI = "https://www.google.com:80/online"
			const auto l_hostPortDelimiter = rest.find(':');
			if(l_hostPortDelimiter == std::string::npos)
			{
				impl_->host_ = rest.substr(2, l_AuthorityEnd - 2);
			}
			else{
				impl_->host_ = rest.substr(2, l_hostPortDelimiter - 2);
				uint32_t l_tmpPortNumber{};
				for(auto chr : rest.substr(l_hostPortDelimiter + 1, l_AuthorityEnd - l_hostPortDelimiter - 1))
				{
					if( (chr < '0')
						||(chr > '9'))
						{
							return false;
						}
						else{
							l_tmpPortNumber *=10;
							l_tmpPortNumber += static_cast<uint16_t>((chr - '0'));
							// Detecting overflow
							if((l_tmpPortNumber & ~((1 << 16)-1)) != 0 )
							{
								return false;
							}
						}
				}
				impl_->port_ = l_tmpPortNumber;
				impl_->hasPort_ = true;
			}
			rest = rest.substr(l_AuthorityEnd);
		}
			// Parsing the path
			impl_->path_.clear();
			if(rest == "/")
			{
				/**
					* Special case of a path that is empty but needs a single
					* empty string element to indicate that it is absolute.
				*/
				impl_->path_.push_back("");
			}
			else if(!rest.empty()){
				for(;;)
				{
					const auto l_PathSegmant = rest.find('/');
					if(l_PathSegmant == std::string::npos)
					{
						impl_->path_.push_back(rest);
						break;
					}
					else{
						impl_->path_.emplace_back(
							rest.begin(), rest.begin() + l_PathSegmant
						);
						rest = rest.substr(l_PathSegmant+1);
					}
				}
			}
			// impl_->path_ = {rest};
		
		return true;
	}

	std::string Uri::GetScheme(void) const
	{
		return impl_->scheme_;
	}
	std::string Uri::GetHost(void) const
	{
		return impl_->host_;
	}
	std::vector<std::string> Uri::GetPath(void) const
	{
		return impl_->path_;
	}
	std::string Uri::GetAuthority(void) const
	{
		return impl_->authority_;
	}
	uint16_t Uri::GetPort(void) const
	{
		return impl_->port_;
	}
	bool Uri::HasPort() const
	{
		return impl_->hasPort_;
	}
	std::string Uri::GetFragment(void) const
	{
		return impl_->fragment_;
	}
	std::string Uri::GetUserInfo(void) const
	{
		return impl_->userInfo_;
	}
	std::string Uri::GetQuery(void) const
	{
		return impl_->query_;
	}
	bool Uri::IsRelativeReference(void) const
	{
		return GetScheme().empty();
	}
	bool Uri::ContainsRelativePath(void) const
	{
		if (impl_->path_.empty())
		{
			return true;
		}
		else
		{
			return !(impl_->path_.front().empty());
		}
	}
}