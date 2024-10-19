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
		std::string GetAuthority(void) const;
		/**
		 * This Method returns an Indication whether or not the URI 
		 * has a port element inside.
		 * 
		 * @return 
		 * 		An Indication whether or not the URI has a port inside.
		 */
		bool HasPort(void) const;
		/**
		* This Methods returns the "port" element of the URI
		*
		* @return
		*		A sring represents the "port" element of the URI if any.
		* @note 
		*	This is returned if there is no "port" element of the URI
		*/
		uint16_t GetPort(void) const;
		/**
		* This Methods returns the "Fragment" element of the URI
		*
		* @return
		*		A sring represents the "Fragment" element of the URI
		* @retval ""
		*	This is returned if there is no "Fragment" element of the URI
		*/
		std::string GetFragment(void) const;
		/**
		* This Methods returns the "Query" element of the URI
		*
		* @return
		*		A sring represents the "Query" element of the URI
		* @retval ""
		*	This is returned if there is no "Query" element of the URI
		*/
		std::string GetQuery(void) const;
		/**
		* This Methods returns the "UserInfo" element of the URI
		*
		* @return
		*		A sring represents the "UserInfo" element of the URI
		* @retval ""
		*	This is returned if there is no "UserInfo" element of the URI
		*/
		std::string GetUserInfo(void) const;
		/**
		 * This Method returns an Indication whether or not the URI 
		 * is relative reference by checking if there is no scheme element then this is
		 * a relative reference.
		 * 
		 * @return 
		 * 		An Indication whether or not the URI is a relative reference.
		 */
		bool IsRelativeReference(void) const;
        /**
		 * This Method returns an Indication whether or not the URI 
		 * contains a relative path by checking if path element starts with "/" 
         * then this is not a relative path.
		 * 
		 * @return 
		 * 		An Indication whether or not the URI contains a relative path.
		 */
		bool ContainsRelativePath(void) const;
        
		/** Private Proberties */
	private:

		struct Impl;
		/** Pimpl Designe pattern to hold all the private implementaions and seperate
		*	them frpm the interfaces.
		*/
		std::unique_ptr<struct Impl> impl_;
	};
}