// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "SingletonWindowFactoryManager.pypp.hpp"

namespace bp = boost::python;

void register_SingletonWindowFactoryManager_class(){

    { //::CEGUI::Singleton< CEGUI::WindowFactoryManager >
        typedef bp::class_< CEGUI::Singleton< CEGUI::WindowFactoryManager >, boost::noncopyable > SingletonWindowFactoryManager_exposer_t;
        SingletonWindowFactoryManager_exposer_t SingletonWindowFactoryManager_exposer = SingletonWindowFactoryManager_exposer_t( "SingletonWindowFactoryManager", bp::init< >() );
        bp::scope SingletonWindowFactoryManager_scope( SingletonWindowFactoryManager_exposer );
        { //::CEGUI::Singleton< CEGUI::WindowFactoryManager >::getSingleton
        
            typedef CEGUI::Singleton< CEGUI::WindowFactoryManager > exported_class_t;
            typedef ::CEGUI::WindowFactoryManager & ( *getSingleton_function_type )(  );
            
            SingletonWindowFactoryManager_exposer.def( 
                "getSingleton"
                , getSingleton_function_type( &::CEGUI::Singleton< CEGUI::WindowFactoryManager >::getSingleton )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        SingletonWindowFactoryManager_exposer.staticmethod( "getSingleton" );
    }

}
