#include "mresource.hpp"
#include "debug.hpp"
#include "utils.hpp"

/******************************************************************************/
#include "providers/noiseprovider.hpp"
#include "providers/textprovider.hpp"
#include "providers/faketracker.hpp"
/******************************************************************************/

#include <regex>





std::unique_ptr<IResourceProvider> IResourceProvider::get(std::string const & name, nlohmann::json const & data)
{
	if(name == "noise")
		return std::make_unique<NoiseProvider>(data);
	if(name == "text")
		return std::make_unique<TextProvider>(data);
	if(name == "fake-tracker")
		return std::make_unique<FakeTracker>(data);

	return nullptr;
}
