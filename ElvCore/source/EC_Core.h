#ifndef EC_Core_H
#define EC_Core_H

#include "EC_Common.h"

namespace ElvCore
{
	class Core : public Ogre::Singleton<Core>
    {
	public:

        Core();
        ~Core();


        bool		initialize(ParameterSet*);
        bool		shutdown();
    
        bool		update(float timestep_);

		template<class T>
		Service*	addService(unsigned int id,std::string name);

		Service*	getService(int serviceID) const  { return serviceID < mServices.size() ? mServices.at(serviceID): NULL; }
		void		reqQuit() { mQuit = true; }

    private:
		typedef std::vector<Service*> ServiceVec;
		ServiceVec mServices;

		bool			mQuit;

        //friend class boost::serialization::access;

        //template<class Archive>
        //void save(Archive & ar_, const unsigned int version_) const
        //{
        //    ar_ & BOOST_SERIALIZATION_NVP(mPhysicService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mGuiService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mAudioService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mAIService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mInputService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mGfxService);
        //}

        //template<class Archive>
        //void load(Archive & ar_, const unsigned int version_)
        //{
        //    ar_ & BOOST_SERIALIZATION_NVP(mPhysicService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mGuiService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mAudioService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mAIService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mInputService);
        //    ar_ & BOOST_SERIALIZATION_NVP(mGfxService);
        //}    

        //BOOST_SERIALIZATION_SPLIT_MEMBER()
    };

}

__declspec(selectany) ElvCore::Core* ElvCore::Core::ms_Singleton = NULL;


#endif