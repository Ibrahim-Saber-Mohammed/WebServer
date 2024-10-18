#include <vector>
#include <memory>
#include <string>
#include <stdint.h>

namespace Uri {
	class Uri {

		/** LifeCycle Management */
	public:

		~Uri();
		Uri(const Uri& obj) =  delete;
		Uri(Uri&& obj) = delete;
		Uri& operator=(const Uri& rhs) = delete;
		Uri& operator=(Uri&& rhs) = delete;

		/** Public interfaces */
	public:
		/**
		* This is a default constructor to create a Uri object
		*/
		Uri();
		Uri(std::string& uriString);

		/**
		* This Methods builds the URI from the elements parsed
		* from a given string rendering of URI 
		* 
		* @param[in] UriString
		* 
		*		A string rendering of URI to Parse
		* @return 	
		*		Retruns an Indication whether or not the URI 
		*		was parsed successfully
		* 
		*/

		bool ParseFromString(const std::string& UriString);

		/**
		* This Methods returns the "scheme" element of the URI 
		*
		* @return
		*		A sring represents the "scheme" element of the URI
		* @retval ""
		*	This is returned if there is no "scheme" element of the URI
		*/
		std::string GetScheme(void) const;

		/**
		* This Methods returns the "host" element of the URI
		*
		* @return
		*		A sring represents the "host" element of the URI
		* @retval ""
		*	This is returned if there is no "host" element of the URI
		*/
		std::string GetHost(void) const;

		/**
		* This Methods returns the "path" element of the URI
		* as a sequence of segments stored in a vector 
		* 
		* @note 
		*	If the first step of the path is an empty string,
		*	then the URI has an absolute path
		* 
		* @return
		*		The "path" element of the URI as a sequence of steps
		*/
		std::vector<std::string> GetPath(void) const;

		/**
		* This Methods returns the "authority" element of the URI
		*
		* @return
		*		A sring represents the "authority" element of the URI
		* @retval ""
		*	This is returned if there is no "authority" element of the URI
		*/
		std::string Uri::GetAuthority(void) const;

		bool HasPort(void) const;
		uint16_t GetPort(void) const;
		/** Private Proberties */
	private:

		struct Impl;
		/** Pimpl Designe pattern to hold all the private implementaions and seperate
		*	them frpm the interfaces.
		*/
		std::unique_ptr<struct Impl> impl_;
	};
}