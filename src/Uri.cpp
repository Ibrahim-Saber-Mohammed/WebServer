#include <Uri/Uri.hpp>

namespace Uri {
	struct Uri::Impl {
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
		bool hasPort_{ false };
		/**
			* This is the "port" element of the URI
		*/
		uint16_t port_{ 0 };
		/**
			* This is the "query" element of the URI
		*/
		std::string query_;
		/**
			* This is the "fregment" element of the URI
		*/
		std::string fregment_;

		/*bool UriHasPort()
		{
			const auto l_PortDelimiter = authority_.find(':');
			return !(l_PortDelimiter == std::string::npos);
		}
		bool ParsePortNumber(std::string& input)
		{
			const auto l_PortDelimiter = authority_.find(':');
			if (UriHasPort())
			{
				host_ = input.substr(2, l_AuthorityEnd - 2);
			}
			else
			{
				host_ = input.substr(2, l_PortDelimiter - 2);
			}
		}*/

	};

	Uri::Uri() : impl_(new Impl) {}
	Uri::~Uri() = default;

	
	bool Uri::ParseFromString(const std::string& UriString)
	{
		//TODO: Refactor this method
		std::string rest{};
		int16_t l_ErrorState{ 0 };
		// Start extracting the scheme element
		const auto l_schemeEnd = UriString.find(':');
		if (l_schemeEnd == std::string::npos)
		{
			impl_->scheme_.clear();
			rest = UriString;
		}
		else
		{
			impl_->scheme_ = UriString.substr(0, l_schemeEnd);
			rest = UriString.substr(l_schemeEnd + 1);

		}
		
		// Extract the authority element
		impl_->hasPort_ = false;
		if (rest.substr(0, 2) == "//")
		{
			const auto l_AuthorityEnd = rest.find('/', 2);
			impl_->authority_ = rest.substr(2, l_AuthorityEnd-2);
			const auto l_PortDelimiter = impl_->authority_.find(':');
			// parse the host element of the URI
			if (l_PortDelimiter == std::string::npos)
			{
				impl_->host_ = rest.substr(2, l_AuthorityEnd - 2);
			}
			else
			{
				impl_->host_ = rest.substr(2, l_PortDelimiter - 2);
				// Parsing the port element of the URI
				uint32_t l_tempPort = 0;
				for (auto chr : rest.substr(l_PortDelimiter + 1, l_AuthorityEnd - l_PortDelimiter - 1))
				{
					if ((chr < '0')
						|| (chr > '9'))
					{
						return false;
					}
					else {
						l_tempPort *= 10 + static_cast<uint16_t>((chr - '0'));
						// detecting overflow
						if (
							(l_tempPort & ~((1 << 16) - 1)) != 0
							)
						{
							return false;
						}
					}
				}
				impl_->port_ = l_tempPort;
				impl_->hasPort_ = true;
			}
			rest = rest.substr(l_AuthorityEnd);
		}
		else
		{
			impl_->host_.clear();
		}

		// Extract the Path element
		impl_->path_.clear();
		if (rest == "/")
		{
			/**
			* Special case of a path that is empty but needs a single
			* empty string element to indicate that it is absolute.
			*/
			impl_->path_.push_back("");
		}
		else if (!rest.empty())
		{
			for (;;)
			{
				const auto l_pathSegment = rest.find("/");
				if (l_pathSegment == std::string::npos)
				{
					impl_->path_.push_back(rest);
					break;
				}
				else {
					impl_->path_.emplace_back(
						rest.begin(), rest.begin() + l_pathSegment
						);
					rest = rest.substr(l_pathSegment + 1);
				}
			}
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
	uint16_t Uri::GetPort(void) const {
		return impl_->port_;
	}
	bool Uri::HasPort() const {
		return impl_->hasPort_;
	}

}