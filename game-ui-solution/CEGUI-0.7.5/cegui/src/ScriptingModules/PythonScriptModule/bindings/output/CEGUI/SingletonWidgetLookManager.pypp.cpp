// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "SingletonWidgetLookManager.pypp.hpp"

namespace bp = boost::python;

void register_SingletonWidgetLookManager_class(){

    { //::CEGUI::Singleton< CEGUI::WidgetLookManager >
        typedef bp::class_< CEGUI::Singleton< CEGUI::WidgetLookManager >, boost::noncopyable > SingletonWidgetLookManager_exposer_t;
        SingletonWidgetLookManager_exposer_t SingletonWidgetLookManager_exposer = SingletonWidgetLookManager_exposer_t( "SingletonWidgetLookManager", bp::init< >() );
        bp::scope SingletonWidgetLookManager_scope( SingletonWidgetLookManager_exposer );
        { //::CEGUI::Singleton< CEGUI::WidgetLookManager >::getSingleton
        
            typedef CEGUI::Singleton< CEGUI::WidgetLookManager > exported_class_t;
            typedef ::CEGUI::WidgetLookManager & ( *getSingleton_function_type )(  );
            
            SingletonWidgetLookManager_exposer.def( 
                "getSingleton"
                , getSingleton_function_type( &::CEGUI::Singleton< CEGUI::WidgetLookManager >::getSingleton )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        SingletonWidgetLookManager_exposer.staticmethod( "getSingleton" );
    }

}
