#ifndef RAPP_CLOUD_COGNITIVE_EXERCISES
#define RAPP_CLOUD_COGNITIVE_EXERCISES
#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class cognitive_test_selector
 * \brief chose a congitive game to play 
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 *
 * \NOTE https://github.com/rapp-project/rapp-platform/tree/master/rapp_web_services/services#cognitive-test-selector
 *		 has changed - will update in 0.7.0
 */
class cognitive_test_selector : public http_request
{
public:

	/// callback functor
	typedef std::function<void(std::vector<std::string>,
                               std::vector<std::string>,
                               std::vector<std::string>,
                               std::string,
                               std::string,
                               std::string)> functor;

	/**
	 * \brief handler obtains a cognitive test from cloud.rapp
	 * \param user set the user
     * \param test_type set the test type
     * \param callback receives arrays of strings and strings
	 */
	cognitive_test_selector(
							const std::string user,
							const std::string test_type,
                            functor callback
						   )
	:http_header("POST /hop/cognitive_test_selector HTTP/1.1\r\n"), 
     http_post(http_header::get_boundary()), 
     delegate_(callback)
	{
        boost::property_tree::ptree tree;
        tree.put("test_type", test_type);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = rapp::misc::json_unquote_pdt_value<bool>()(ss.str(), recursive);
        http_post::add_content("json", json, false);

	}

    /**
     * \brief handle platform's JSON reply
     */
	void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        std::vector<std::string> questions;
        std::vector<std::string> possib_ans;
        std::vector<std::string> correct_ans;
        std::string test_instance;
        std::string test_type;
        std::string test_subtype;
        
        json::const_iterator it =json.find("questions");
        if (it == json.end()){
            throw std::runtime_error("no questions in cognitive exercise");
        }
        else {
            questions = it->get<std::vector<std::string>>();
        }

        json::const_iterator it_pa =json.find("possib_ans");
        if (it_pa == json.end()){
            throw std::runtime_error("no possible answers in cognitive exercise");
        }
        else {
            possib_ans = it_pa->get<std::vector<std::string>>();
        }

        json::const_iterator it_ca =json.find("correct_ans");
        if (it_ca == json.end()){
            throw std::runtime_error("no correct answers in cognitive exercise");
        }
        else {
            correct_ans = it_ca->get<std::vector<std::string>>();
        }

        json::const_iterator it_ti = json.find("test_instance");
        if (it_ti == json.end()){
            throw std::runtime_error("no test instance in cognitive exercise");
        }
        else {
            test_instance = it_ti->get<std::string>();
        }
        
        json::const_iterator it_type = json.find("test_type");
        if (it_type == json.end()){
            throw std::runtime_error("no test type in cognitive exercise");
        }
        else {
            test_type = it_type->get<std::string>();
        }

        json::const_iterator it_sub = json.find("test_subtype");
        if (it_sub== json.end()){
            throw std::runtime_error("no test subtype in cognitive exercise");
        }
        else {
            test_subtype = it_sub->get<std::string>();
        }

        json::const_iterator it_error = json.find("error");
        if (it_error== json.end()){
            throw std::runtime_error("no error param in cognitive exercise");
        }
        else {
            error = it_error->get<std::string>();
            if (!error.empty()) {
                std::cerr << "cognitive_test_selector JSON error: " << error <<std::endl;
            }
        }

        /*try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            // NOTE: untested!
            for (auto child : tree.get_child("questions")) {
                questions.push_back(child.second.get_value<std::string>());
            }
            for (auto child : tree.get_child("possib_ans")) {
                possib_ans.push_back(child.second.get_value<std::string>());
            }
            for (auto child : tree.get_child("correct_ans")) {
                correct_ans.push_back(child.second.get_value<std::string>());
            }
            for (auto child : tree.get_child("test_instance")) {
                test_instance = child.second.get_value<std::string>();
            }
            for (auto child : tree.get_child("test_type")) {
                test_type = child.second.get_value<std::string>();
            }
            for (auto child : tree.get_child("test_subtype")) {
                test_subtype = child.second.get_value<std::string>();
            }
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "cognitive_test_selector JSON error: " << value << std::endl;
                }
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "cognitive_test_selector::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }*/
        delegate_(questions,
                  possib_ans,
                  correct_ans,
                  test_instance,
                  test_type,
                  test_subtype);
    }

    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    /// 
    std::function<void(std::vector<std::string>,
                       std::vector<std::string>,
                       std::vector<std::string>,
                       std::string,
                       std::string,
                       std::string)> delegate_;
};

/**
 * \class cognitive_record_performance
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_record_performance : public caller, public http_request
{
public:
    /**
     * \brief record performance for a cognitive test
     * \param test_instance sets the actual test
     * \param score is the recorded score
     * \param callback receives the platform's response
     */
     cognitive_record_performance(
                                    const std::string test_instance,
                                    const float score,
                                    std::function<void(std::string)> callback
                                 )
    : http_header("POST /hop/cognitive_record_performance HTTP/1.1\r\n"),
      http_post(http_header::get_boundary()),
      delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("test_instance", test_instance);
        tree.put("score", score);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

        std::string json = rapp::misc::json_unquote_pdt_value<float>()(ss.str(), score);
        http_post::add_content("json", json, false); 
        http_post::end();
 
    }

    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        std::string performance_entry;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // NOTE: untested!
            for (auto child : tree.get_child("performance_entry")) {
                performance_entry = child.second.get_value<std::string>();
            }

            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "cognitive_record_performance JSON error: " << value << std::endl;
                }
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "cognitive_record_performance::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(performance_entry);
    }


    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    ///
    std::function<void(std::string)> delegate_;
};

/**
 * \class cognitive_get_history
 * \version 0.7.0
 * \date 15 August 2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_get_history : public caller, public http_request
{
public:
    /**
     * \brief get history of cognitive game
     * \param from_time is a unix timestamp
     * \param to_time is a unix timestamp
     * \param test_type is the cognitive test
     * \param callback will receive a JSON reply
     */
    cognitive_get_history(
                            unsigned int from_time,
                            unsigned int to_time,
                            const std::string test_type,
                            std::function<void(std::string)> callback
                         )
    : http_header("POST /hop/cognitive_get_history HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()),
      delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("from_time", from_time);
        tree.put("to_time", to_time);
        tree.put("test_type", test_type);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		// JSON PDT value unquote (call twice!)
		auto str = misc::json_unquote_pdt_value<unsigned int>()(ss.str(), from_time);
        std::string json= misc::json_unquote_pdt_value<unsigned int>()(str, to_time);
        http_post::add_content("json", json, false); 
        http_post::end();

    }
    /**
     * \brief forward (don't parse) platform reply
     */
    void deserialise(std::string json) const
    {
        delegate_(std::move(json));
    }

    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:

    std::function<void(std::string)> delegate_;
};

/**
 * \class cognitive_get_scores
 * \version 0.7.0
 * \date 15 August  2016
 * \author Alex Giokas <a.gkiokas@ortelio.co.uk>
 */
class cognitive_get_scores :  public caller, public http_request
{
public:
    /**
     * \brief get cognitive test scores
     * \param up_to_time defines scores queried up to that unix timestamp
     * \param test_type the test type
     * \param callback will receive an array of test classes and respective scores
     */
    cognitive_get_scores(
                          unsigned int up_to_time,
                          const std::string test_type,
                          std::function<void(std::vector<unsigned int>, std::vector<float>)> callback
                        )
    : http_header("POST /hop/cognitive_get_scores HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()),
      delegate_(callback)
    {
        boost::property_tree::ptree tree;
        tree.put("up_to_time", up_to_time);
        tree.put("test_type", test_type);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);

		// JSON PDT value unquote
        std::string json = rapp::misc::json_unquote_pdt_value<unsigned int>()(ss.str(), up_to_time);
        http_post::add_content("json", json, false); 
        http_post::end();
    }

    /**
     * \brief handle platform's JSON reply
     */
    void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        std::vector<unsigned int> test_classes;
        std::vector<float> scores;
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);

            // NOTE: untested!
            for (auto child : tree.get_child("test_classes")) {
                test_classes.push_back(child.second.get_value<unsigned int>());
            }

            for (auto child : tree.get_child("scores")) {
                scores.push_back(child.second.get_value<float>());
            }

            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "cognitive_get_scores JSON error: " << value << std::endl;
                }
            }
	    }
        catch (boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "cognitive_get_scores::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(test_classes, scores);
    }


    /**
    * \brief method to fill the buffer with http_post and http_header information
    * \param info is the data of the platform    
    */
    boost::asio::streambuf fill_buffer(rapp::cloud::platform info)
    {
           return std::move(http_request::fill_buffer(info));
    }

private:
    ///
    std::function<void(std::vector<unsigned int>,
                       std::vector<float>)> delegate_;
};
}
}
#endif
