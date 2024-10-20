#include <Uri/Uri.hpp>
#include <iostream>
namespace Uri
{
	namespace
	{
		bool ConvertStringToUint16Number(const std::string &StringNumber, uint16_t &Number)
		{
			uint32_t l_tmpPortNumber{};
			for (auto chr : StringNumber)
			{
				// Detecting Characters and negative numbers
				if ((chr < '0') || (chr > '9'))
				{
					return false;
				}
				else
				{
					l_tmpPortNumber *= 10;
					l_tmpPortNumber += static_cast<uint16_t>((chr - '0'));
					// Detecting overflow
					if ((l_tmpPortNumber & ~((1 << 16) - 1)) != 0)
					{
						return false;
					}
				}
			}
			Number = static_cast<uint16_t>(l_tmpPortNumber);
			return true;
		}
	}
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
		
		bool ParseUriSchemeElement(const std::string &Copy_strUriString, std::string &UriRemainningStringElements)
		{
			const auto l_SchemeEnd = Copy_strUriString.find(':');
			if (l_SchemeEnd == std::string::npos)
			{
				scheme_.clear();
				UriRemainningStringElements = Copy_strUriString;
			}
			else
			{
				scheme_ = Copy_strUriString.substr(0, l_SchemeEnd);
				UriRemainningStringElements = Copy_strUriString.substr(l_SchemeEnd + 1);
			}
			return true;
		}
		bool ParseUriFragmentElement(const std::string &Copy_strUriString, std::string &UriRemainningStringElements)
		{
			auto l_FragmentDelimiter = Copy_strUriString.find('#');
			if (l_FragmentDelimiter == std::string::npos)
			{
				fragment_.clear();
				l_FragmentDelimiter = Copy_strUriString.length();
			}
			else
			{
				fragment_ = Copy_strUriString.substr(l_FragmentDelimiter + 1);
			}
			UriRemainningStringElements = Copy_strUriString.substr(0, l_FragmentDelimiter);
			return true;
		}
		bool ParseUriQueryElement(const std::string &Copy_strUriString, std::string &UriRemainningStringElements){
			auto l_QueryDelimiter = Copy_strUriString.find('?');
			if (l_QueryDelimiter == std::string::npos)
			{
				query_.clear();
				l_QueryDelimiter = Copy_strUriString.length();
			}
			else
			{
				query_ = Copy_strUriString.substr(l_QueryDelimiter + 1, Copy_strUriString.length());
			}

			UriRemainningStringElements = Copy_strUriString.substr(0, l_QueryDelimiter);
			return true;
		}
		bool ParseUriPathElement(std::string &Copy_strPathString)
		{
			path_.clear();
			if (Copy_strPathString == "/")
			{
				/**
				 * Special case of a path that is empty but needs a single
				 * empty string element to indicate that it is absolute.
				 */
				path_.push_back("");
			}
			else if (!Copy_strPathString.empty())
			{
				for (;;)
				{
					const auto l_PathSegmant = Copy_strPathString.find('/');
					if (l_PathSegmant == std::string::npos)
					{
						path_.push_back(Copy_strPathString);
						break;
					}
					else
					{
						path_.emplace_back(
							Copy_strPathString.begin(), Copy_strPathString.begin() + l_PathSegmant);
						Copy_strPathString = Copy_strPathString.substr(l_PathSegmant + 1);
					}
				}
			}
			return true;
		}
	};

	Uri::Uri() : impl_(new Impl) {}
	Uri::~Uri() = default;

	bool Uri::ParseFromString(const std::string &UriString)
	{
		// TODO: Refactor this method
		std::string UriStringWithoutScheme{};
		std::string l_UriPathString{};
		std::string l_UriAuthourityPathQuery{};
		const auto l_SchemeEnd = UriString.find(':');

		if (!impl_->ParseUriSchemeElement(UriString, UriStringWithoutScheme))
		{
			return false;
		}
		// Parsing the Authority, host and port
		impl_->hasPort_ = false;
		if (UriStringWithoutScheme.substr(0, 2) == "//")
		{
			// paring the Fragment
			if(!impl_->ParseUriFragmentElement(UriStringWithoutScheme, l_UriAuthourityPathQuery))
			{
				return false;
			}
			if(!impl_->ParseUriQueryElement(l_UriAuthourityPathQuery, l_UriAuthourityPathQuery))
			{
				return false;
			}
			UriStringWithoutScheme = l_UriAuthourityPathQuery;

			auto l_userInfoDelimiter = UriStringWithoutScheme.find('@');
			if (l_userInfoDelimiter == std::string::npos)
			{
				l_userInfoDelimiter = UriStringWithoutScheme.length();
				impl_->userInfo_.clear();
			}
			else
			{
				impl_->userInfo_ = UriStringWithoutScheme.substr(2, l_userInfoDelimiter - 2);
				UriStringWithoutScheme.erase(2, l_userInfoDelimiter - 1);
			}

			// Parsing the authority host and port number
			auto l_AuthorityEnd = UriStringWithoutScheme.find('/', 2);
			// URI = "https://www.google.com"
			if (l_AuthorityEnd == std::string::npos)
			{
				l_AuthorityEnd = UriStringWithoutScheme.length();
			}
			// URI = "https://www.google.com/online"
			impl_->authority_ = UriStringWithoutScheme.substr(2, l_AuthorityEnd - 2);
			// Check for the userInfo in the URI

			// URI = "https://www.google.com:80/online"
			const auto l_hostPortDelimiter = UriStringWithoutScheme.find(':');
			if (l_hostPortDelimiter == std::string::npos)
			{
				impl_->host_ = UriStringWithoutScheme.substr(2, l_AuthorityEnd - 2);
			}
			else
			{
				impl_->host_ = UriStringWithoutScheme.substr(2, l_hostPortDelimiter - 2);
				const auto authourity = UriStringWithoutScheme.substr(l_hostPortDelimiter + 1, l_AuthorityEnd - l_hostPortDelimiter - 1);
				if (!ConvertStringToUint16Number(authourity, impl_->port_))
				{
					return false;
				}
				impl_->hasPort_ = true;
			}
			UriStringWithoutScheme = UriStringWithoutScheme.substr(l_AuthorityEnd);
		}
		else{
			impl_->port_ = 0;
			impl_->hasPort_ = false;
		}

		l_UriPathString = UriStringWithoutScheme;
		// Parsing the path
		if (!impl_->ParseUriPathElement(l_UriPathString))
		{
			return false;
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