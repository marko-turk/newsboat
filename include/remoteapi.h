#ifndef NEWSBOAT_REMOTEAPI_H_
#define NEWSBOAT_REMOTEAPI_H_

#include <curl/curl.h>
#include <string>
#include <utility>
#include <vector>

#include "configcontainer.h"

namespace newsboat {

typedef std::pair<std::string, std::vector<std::string>> TaggedFeedUrl;

typedef struct {
	std::string user;
	std::string pass;
	std::string token;
} Credentials;

class RemoteApi {
public:
	explicit RemoteApi(ConfigContainer* c)
		: cfg(c)
	{
	}
	virtual ~RemoteApi() {}
	virtual bool authenticate() = 0;
	virtual std::vector<TaggedFeedUrl> get_subscribed_urls() = 0;
	virtual void add_custom_headers(curl_slist** custom_headers) = 0;
	virtual bool mark_all_read(const std::string& feedurl) = 0;
	virtual bool mark_article_read(const std::string& guid, bool read) = 0;
	virtual bool mark_articles_read(const std::vector<std::string>& guids);
	virtual bool update_article_flags(const std::string& oldflags,
		const std::string& newflags,
		const std::string& guid) = 0;
	static const std::string read_password(const std::string& file);
	static const std::string eval_password(const std::string& cmd);

protected:
	ConfigContainer* cfg;
	Credentials get_credentials(const std::string& scope,
		const std::string& name);
};

} // namespace newsboat

#endif /* NEWSBOAT_REMOTEAPI_H_ */
