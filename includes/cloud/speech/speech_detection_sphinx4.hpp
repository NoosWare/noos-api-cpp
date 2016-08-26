#ifndef RAPP_CLOUD_SPEECH_TO_TEXT_SPHINX4
#define RAPP_CLOUD_SPEECH_TO_TEXT_SPHINX4
/**
 * Copyright 2015 RAPP
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * #http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "includes.ihh"
namespace rapp {
namespace cloud {
/**
 * \class speech_detection_sphinx4
 * \brief speech-to-text recognition using CMU sphinx4
 * \version 0.7.0
 * \date 26 August 2016
 * \author Alex Gkiokas <a.gkiokas@ortelio.co.uk>
 */
template<class T>
class speech_detection_sphinx4 : public caller, public http_request
{
public:
    /**
     * \brief construct a speechToText handler
     * \param audio is the actual binary sound file
     * \param language is the language used for speech to text
     * \param grammar is the Grammars used in Spc2Txt
     * \param user is the user token
     * \param words will be searched for in the audio
     * \param sentences will be under consideration
     * \param callback will be executed once the rapp cloud has responded
     */
    speech_detection_sphinx4(
							  const T audiofile;
                              const std::string language,
							  const std::string user,
							  const std::vector<std::string> grammar,
							  const std::vector<std::string> words,
							  const std::vector<std::string> sentences,
							  std::function<void(std::vector<std::string> words)> callback
						    )
	: http_header("POST /hop/ontology_subclasses_of HTTP/1.1\r\n"), 
      http_post(http_header::get_boundary()), 
      delegate_(callback)
    {
        assert(audiofile);
        std::string fname =  rapp::misc::random_boundary() + audiofile->extension(); 

        boost::property_tree::ptree tree;
        tree.put("language", language);
        tree.put("user", user);
        tree.put("audio_source", audiofile->audio_source());

        boost::property_tree::ptree grammar_array;
        for (const auto gram : grammar) {
            boost::property_tree::ptree child;
            child.put("", gram);
            grammar_array.push_back(std::make_pair("", child));
        }
        tree.add_child("grammar", grammar_array);

        boost::property_tree::ptree words_array;
        for (const auto word : words) {
            boost::property_tree::ptree child;
            child.put("", word);
            words_array.push_back(std::make_pair("", child));
        }
        tree.add_child("words", words_array);

        boost::property_tree::ptree sentence_array;
        for (const auto sents : sentences) {
            boost::property_tree::ptree child;
            child.put("", sents);
            sentence_array.push_back(std::make_pair("", child));
        }
        tree.add_child("sentences", sentence_array);

        std::stringstream ss;
        boost::property_tree::write_json(ss, tree, false);
        std::string json = ss.str();

        http_post::add_content("json", json, false);
        auto bytes = audiofile->bytearray();
        http_post::add_content("file", fname, bytes);
        http_post::end();
    
    }


    /**
	 * \brief handle the rappl-platform JSON reply
	 */ 
    void deserialise(std::string json) const
    {
        std::stringstream ss(json);
        std::vector<std::string> words;        
        try {
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(ss, tree);
            // JSON response is: { words: [], error: '' } 
            for (auto child : tree.get_child("words")) {
                words.push_back(child.second.get_value<std::string>());
			}
            // Check for error response from api.rapp.cloud
            for (auto child : tree.get_child("error")) {
                const std::string value = child.second.get_value<std::string>();
                if (!value.empty()) {
                    std::cerr << "speech_detection_sphinx4 error: " << value << std::endl;
				}
            }
        }
        catch(boost::property_tree::json_parser::json_parser_error & je) {
            std::cerr << "speech_detection_sphinx4::handle_reply Error parsing: " << je.filename() 
                      << " on line: " << je.line() << std::endl;
            std::cerr << je.message() << std::endl;
        }
        delegate_(words);
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
    /// The callback called upon completion of receiving the detected words
    std::function<void(std::vector<std::string> words)> delegate_;
};
}
}
#endif
