#include <Uri/Uri.hpp>
#include <iostream>
#include <functional>
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
		bool ExecuteValidationStartegy(const std::string &CopyString, std::function<bool(char, bool)> PassingStartegy)
		{
			for (const auto ch : CopyString)
			{
				if (PassingStartegy(ch, false))
				{
					return true;
				}
			}
			return PassingStartegy(' ', true);
		}
		std::function<bool(char, bool)> LegalSchemeValidationStartegy()
		{
			std::shared_ptr<bool>isFirstCharacter = std::make_shared<bool>(true);
			return [isFirstCharacter](char chr, bool endOfString) -> bool
			{
				if (endOfString)
				{
					return !(*isFirstCharacter);
				}
				else
				{
					bool Check{false};
					if ((*isFirstCharacter))
					{
						Check = (std::isalpha(chr));
					}
					else
					{
						Check = (std::isalpha(chr) || std::isdigit(chr) || (chr == '+') || (chr == '-') || (chr == '.'));
					}
					*isFirstCharacter = false;
					return Check;
				}
				return false;
			};
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

		/**
		 * This Method parses the scheme element of a URI string and returns the remaining URI elemnets.
		 * 
		 * @param[in] Copy_strUriString
		 * 			a URI string containing all the URI elements
		 * @param[in] UriRemainningStringElements
		 * 			string reference to store the remainng elements of the URI after paring the scheme.
		 * @param[out] UriRemainningStringElements
		 * 			string conatining the remainng elements of the URI after paring the scheme.
		 * 
		 * @return 
		 * 			An Indication whether or not the scheme part is parsed successfully and passed the validation strategy
		 * 			and it's complient with the standard. 
		 */
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
				if( !ExecuteValidationStartegy(scheme_, LegalSchemeValidationStartegy()))
				{
					return false;
				}
				UriRemainningStringElements = Copy_strUriString.substr(l_SchemeEnd + 1);
			}
			return true;
		}

		/**
		 * This Method parses the Fragment element of a URI string and returns the remaining URI elemnets.
		 * 
		 * @param[in] Copy_strUriString
		 * 			a URI string containing all the URI elements
		 * @param[in] UriRemainningStringElements
		 * 			string reference to store the remainng elements of the URI after paring the Fragment.
		 * @param[out] UriRemainningStringElements
		 * 			string conatining the remainng elements of the URI after paring the Fragment.
		 * 
		 * @return 
		 * 			An Indication whether or not the Fragment part is parsed successfully and passed the validation strategy
		 * 			and it's complient with the standard. 
		 */
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
		/**
		 * This Method parses the Query element of a URI string and returns the remaining URI elemnets.
		 * 
		 * @param[in] Copy_strUriString
		 * 			a URI string containing all the URI elements
		 * @param[in] UriRemainningStringElements
		 * 			string reference to store the remainng elements of the URI after paring the Query.
		 * @param[out] UriRemainningStringElements
		 * 			string conatining the remainng elements of the URI after paring the Query.
		 * 
		 * @return 
		 * 			An Indication whether or not the Query part is parsed successfully and passed the validation strategy
		 * 			and it's complient with the standard. 
		 */
		bool ParseUriQueryElement(const std::string &Copy_strUriString, std::string &UriRemainningStringElements)
		{
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
		/**
		 * This Method parses the Path element of a URI string and returns the remaining URI elemnets.
		 * 
		 * @param[in] Copy_strUriString
		 * 			a URI string containing all the URI elements
		 * @param[out] Copy_strUriString
		 * 			string conatining the remainng elements of the URI after paring the Path.
		 * 
		 * @return 
		 * 			An Indication whether or not the Path part is parsed successfully and passed the validation strategy
		 * 			and it's complient with the standard. 
		 */
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
		bool ParseUriUserInfoElement(const std::string &Copy_strUriString, std::string &UriRemainningStringElements)
		{
			UriRemainningStringElements = Copy_strUriString;
			auto l_userInfoDelimiter = Copy_strUriString.find('@');
			if (l_userInfoDelimiter == std::string::npos)
			{
				l_userInfoDelimiter = Copy_strUriString.length();
				userInfo_.clear();
			}
			else
			{
				userInfo_ = Copy_strUriString.substr(2, l_userInfoDelimiter - 2);
				UriRemainningStringElements.erase(2, l_userInfoDelimiter - 1);
			}
			return true;
		}
		bool ParsingHostAndPort(std::string &Copy_strUriString, size_t Copy_AuthorityEndIndex)
		{
			// URI = "https://www.google.com:80/online"
			const auto l_hostPortDelimiter = Copy_strUriString.find(':');
			if (l_hostPortDelimiter == std::string::npos)
			{
				host_ = Copy_strUriString.substr(2, Copy_AuthorityEndIndex - 2);
			}
			else
			{
				host_ = Copy_strUriString.substr(2, l_hostPortDelimiter - 2);
				const auto authourity = Copy_strUriString.substr(l_hostPortDelimiter + 1, Copy_AuthorityEndIndex - l_hostPortDelimiter - 1);
				if (!ConvertStringToUint16Number(authourity, port_))
				{
					return false;
				}
				hasPort_ = true;
			}
			return true;
		}
		bool ParesUriAuthorityElements(const std::string &Copy_strUriString, std::string &UriRemainningStringElements)
		{
			UriRemainningStringElements = Copy_strUriString;
			auto l_AuthorityEnd = UriRemainningStringElements.find('/', 2);
			// URI = "https://www.google.com"
			if (l_AuthorityEnd == std::string::npos)
			{
				l_AuthorityEnd = UriRemainningStringElements.length();
			}
			// URI = "https://www.google.com/online"
			authority_ = UriRemainningStringElements.substr(2, l_AuthorityEnd - 2);

			if (!ParseUriUserInfoElement(UriRemainningStringElements, UriRemainningStringElements))
			{
				return false;
			}
			if (!ParsingHostAndPort(UriRemainningStringElements, l_AuthorityEnd))
			{
				return false;
			}
			UriRemainningStringElements = UriRemainningStringElements.substr(l_AuthorityEnd);
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
		std::string l_UriAuthourityPath{};
		std::string l_UriAuthourityPathQuery{};
		// Parsing the Authority, host and port
		impl_->hasPort_ = false;

		if (!impl_->ParseUriSchemeElement(UriString, UriStringWithoutScheme))
		{
			return false;
		}
		if (UriStringWithoutScheme.substr(0, 2) == "//")
		{
			// paring the Fragment
			if (!impl_->ParseUriFragmentElement(UriStringWithoutScheme, l_UriAuthourityPathQuery))
			{
				return false;
			}
			// paring the Query
			if (!impl_->ParseUriQueryElement(l_UriAuthourityPathQuery, l_UriAuthourityPath))
			{
				return false;
			}
			// Parsing Authority

			if (!impl_->ParesUriAuthorityElements(l_UriAuthourityPath, l_UriPathString))
			{
				return false;
			}
		}
		else
		{
			impl_->port_ = 0;
			impl_->hasPort_ = false;
		}

		l_UriPathString = UriStringWithoutScheme;
		// Parsing the path
		if (!impl_->ParseUriPathElement(l_UriPathString))
		{
			return false;
		}
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