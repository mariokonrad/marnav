#include <iostream>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#if defined(__linux__)
	#include <getopt.h>
	#include <string>
	#include <exception>
	#include <vector>
	#include <fstream>
	#include <cassert>
#endif


#if defined(__linux__) // do not care about windows at the moment (affects only CppUnit output)

// FIXME: this should be moved to its own file, no preprocessor stuff

/// A listener for google test which collects results on performed tests
/// and prints them in the CppUnit format (XML). This is useful for futher
/// processing of unit test results, where the google test format (JUnit)
/// does not suffice (commercial C++ plugin for SonarQube for example).
///
/// @note This is implemented inline, just because this implementation
///       is done lazy. In the context it is used, its easier to handle.
class CppUnitPrinter : public ::testing::EmptyTestEventListener
{
public:
	void dump(std::ostream& os)
	{
		using namespace std;

		size_t failures_total = 0;
		size_t errors = 0;
		size_t failures = 0;
		size_t test_id = 0;

		os << "<?xml version=\"1.0\" encoding='ISO-8859-1' standalone='yes' ?>" << endl;
		os << "<TestRun>" << endl;

		os << "  <FailedTests>" << endl;
		for (Tests::const_iterator test = tests.begin(); test != tests.end(); ++test) {
			if (test->failed) {
				++failures_total;
				++failures;
				++test_id;
				os << "    <Test id=\"" << test_id << "\">" << endl;
				os << "      <Name>" << test->test_case << "::" << test->name << "</Name>" << endl;
				os << "      <Message>" << test->message <<  "</Message>" << endl;
				os << "      <FailureType>1</FailureType>" << endl;
				os << "      <Location>" << endl;
				os << "        <File>" << test->file_name << "</File>" << endl;
				os << "        <Line>" << test->line_number << "</Line>" << endl;
				os << "      </Location>" << endl;
				os << "    </Test>" << endl;
			}
		}
		os << "  </FailedTests>" << endl;

		os << "  <SuccessfulTests>" << endl;
		for (Tests::const_iterator test = tests.begin(); test != tests.end(); ++test) {
			if (!test->failed) {
				++test_id;
				os << "    <Test id=\"" << test_id << "\">" << endl;
				os << "      <Name>" << test->test_case << "::" << test->name << "</Name>" << endl;
				os << "      <FailureType>0</FailureType>" << endl;
				os << "    </Test>" << endl;
			}
		}
		os << "  </SuccessfulTests>" << endl;

		os << "  <Statistics>" << endl;
		os << "    <Tests>" << tests.size() << "</Tests>" << endl;
		os << "    <FailuresTotal>" << failures_total << "</FailuresTotal>" << endl;
		os << "    <Errors>" << errors << "</Errors>" << endl;
		os << "    <Failures>" << failures << "</Failures>" << endl;
		os << "  </Statistics>" << endl;

		os << "</TestRun>" << endl;
	}

public:
	virtual void OnTestStart(const ::testing::TestInfo& info)
	{
		assert(current.test_case == "");
		assert(current.name == "");
		current.test_case = info.test_case_name();
		current.name = info.name();
	}

	virtual void OnTestPartResult(const ::testing::TestPartResult& info)
	{
		current.failed = info.failed() != 0;
		current.message = info.message();
		current.file_name = info.file_name();
		current.line_number = info.line_number();
	}

	virtual void OnTestEnd(const ::testing::TestInfo& info)
	{
		assert(current.test_case == info.test_case_name());
		assert(current.name == info.name());
		tests.push_back(current);
		current = TestInformation();
	}

private:
	struct TestInformation
	{
		TestInformation()
			: failed(false)
		{}

		bool failed;
		std::string test_case;
		std::string name;
		std::string message;
		std::string file_name;
		int line_number;
	};

	typedef std::vector<TestInformation> Tests;

	Tests tests;
	TestInformation current;
};

namespace params {

/// Stores options pared from command line options.
///
/// @note This is implemented inline, just because this implementation
///       is done lazy. In the context it is used, its easier to handle.
class Options
{
public:
	enum Index
	{
		OPT_HELP = 0,
		OPT_CPPUNIT_OUTPUT = 1,
		OPT_DATA_ROOT = 2,
	};

	Options()
		: cppunit_output(false)
		, cppunit_output_filename("")
		, data_root(".")
	{}

	void print_usage()
	{
		using namespace std;

		cout << endl;
		cout << "Additional Options:" << endl;
		cout << "  --cppunit-output [=filename]  : Writes cppunit XML format output" << endl;
		cout << "                                  into the specified file. If no" << endl;
		cout << "                                  filename is specified, the output" << endl;
		cout << "                                  is writtend to stderr." << endl;
		cout << endl;
		cout << "  --data-root path              : sets the global data root path." << endl;
		cout << "                                  this is useful if the paths differ" << endl;
		cout << "                                  during unit tests." << endl;
		cout << endl;
	}

	const char* get_options() const
	{
		static const char* OPTIONS = "h";
		return OPTIONS;
	}

	const struct option* get_long_options() const
	{
		static const struct option LONG_OPTIONS[] =
		{
			{ "help",           no_argument,       0, 'h' },
			{ "cppunit-output", optional_argument, 0, 0   },
			{ "data-root",      required_argument, 0, 0   },
			{ 0,                no_argument,       0, 0   }
		};

		return LONG_OPTIONS;
	}

public:
	bool cppunit_output; ///< Write output in cppunit format (XML)
	std::string cppunit_output_filename; ///< Filename to write tht cppunit output to
	std::string data_root; ///< Path to the data root
};

/// Parses the command line options left overs.
///
/// This function may throw std::runtime_error if command line
/// arguments are wrong.
Options parse(int& argc, char** argv)
{
	// using getopt_long instead of boost::program_options because
	// boost introduces additional dependencies, which are not
	// desired at this point.
	// boost::program_options would normally be preferred.

	Options options;

	while (true) {
		int index = -1;
		int result = getopt_long(argc, argv,
			options.get_options(), options.get_long_options(), &index);

		if (result == -1)
			break;

		switch (result) {
			case 'h':
				options.print_usage();
				break;

			case 0:
				switch (static_cast<Options::Index>(index)) {
					case Options::OPT_HELP:
						options.print_usage();
						break;

					case Options::OPT_CPPUNIT_OUTPUT:
						options.cppunit_output = true;
						if (optarg) {
							options.cppunit_output_filename = optarg;
						}
						break;

					case Options::OPT_DATA_ROOT:
						options.data_root = optarg;
						break;
				}
				break;

			default:
				throw std::runtime_error("unknown parameter");
		}
	}

	return options;
}

}

#endif

#if defined(__linux__)
static params::Options options;

namespace testing {
namespace global {

std::string data_root()
{
	return options.data_root;
}

}}
#endif

GTEST_API_ int main(int argc, char** argv)
{
	testing::InitGoogleMock(&argc, argv);

#if defined(__linux__)
	// argc/argv used by GoogleTest/-Mock were consumed
	options = params::parse(argc, argv);

	CppUnitPrinter* printer = 0;

	if (options.cppunit_output) {
		printer = new CppUnitPrinter;
		::testing::UnitTest::GetInstance()->listeners().Append(printer);
	}
#endif

	int rc = RUN_ALL_TESTS();

#if defined(__linux__)
	if (options.cppunit_output) {
		if (options.cppunit_output_filename.empty()) {
			printer->dump(std::cerr);
		} else {
			std::ofstream os(options.cppunit_output_filename.c_str());
			printer->dump(os);
		}
	}
#endif

	return rc;
}

