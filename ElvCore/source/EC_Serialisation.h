#ifndef EC_SERIALISATION_H
#define EC_SERIALISATION_H

#include <string>
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/set.hpp>
#include <boost/filesystem.hpp>

namespace ElvCore
{
    class Serialise
    {
    public:
        Serialise(std::string const & filename_)
			: _outputArchive(0)       
		{
			boost::filesystem::create_directories(boost::filesystem::path(filename_).remove_leaf());

			_outFile.open(filename_.c_str());
            if(!_outFile.is_open())
            {
                throw std::runtime_error("Could not open " + filename_ + " for serialisation.");
            }

            _outputArchive = new boost::archive::text_oarchive(_outFile);
        }

        ~Serialise(void)
        {
            delete _outputArchive;
        }

        template<class Out>
        bool out(Out const & out_)
        {
            (*_outputArchive) << out_;
            return true;
        }

    private:
        std::ofstream _outFile;
        boost::archive::text_oarchive * _outputArchive;
    };

    class Deserialise
    {
    public:
        Deserialise(std::string const & filename_)
            :  _inputArchive(0)
        {
			boost::filesystem::create_directories(boost::filesystem::path(filename_).remove_leaf());

			_inputFile.open(filename_.c_str());
            if(!_inputFile.is_open())
            {
                throw std::runtime_error("Could not open " + filename_ + " for serialisation.");
            }

            _inputArchive = new boost::archive::text_iarchive(_inputFile);
        }

        ~Deserialise(void)
        {
            delete _inputArchive;
        }

        template<class In>
        bool in(In & in_)
        {
            (*_inputArchive) >> in_;
            return true;
        }

    private:
        std::ifstream _inputFile;
        boost::archive::text_iarchive * _inputArchive;
    };
}

#endif
