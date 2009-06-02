#ifndef EG_CONTROLLER_H
#define EG_CONTROLLER_H

#include "ElvCore.h"

namespace ElvGame
{
	class Controller : public ElvCore::Component
	{
	public:
		Controller();
		~Controller();

		bool update(float timestep);
	private:
		std::string getType() { return "Controller"; }

	private:
		
		friend class boost::serialization::access;

		template<class Archive>
		void save(Archive & ar_, const unsigned int version_) const
		{
			ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);
			
		}

		template<class Archive>
		void load(Archive & ar_, const unsigned int version_)
		{
			ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);
		}    

        BOOST_SERIALIZATION_SPLIT_MEMBER()
	};

	BOOST_CLASS_EXPORT_GUID(Controller, "ElvGameController")

}
#endif