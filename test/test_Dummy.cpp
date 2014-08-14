#include <boost/test/unit_test.hpp>
#include <dps_desertstar-ssp1/Dummy.hpp>

using namespace dps_desertstar-ssp1;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    dps_desertstar-ssp1::DummyClass dummy;
    dummy.welcome();
}
