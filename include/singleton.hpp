#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

#include "typetraits.hpp"
#include "threads.hpp"
#include <stdexcept>

namespace SGT {

/*	template<typename T>
	class NoCreation {
	protected : 
		inline explicit NoCreation() {}
		inline ~NoCreation() {}

		//	creation/destruction/storage issues
		inline static T* CreateInstance() { throw std::logic_error("NoCreation::CreateInstance called"); }
		inline static void DestroyInstance(T*) { throw std::logic_error("NoCreation::DestroyInstance called"); }

	private : 
		inline explicit NoCreation(NoCreation const&) {}
		inline NoCreation& operator=(NoCreation const&) { return *this; }
	};
*/
	template<typename T>
	class CreateUsingNew {
	protected : 
		inline explicit CreateUsingNew() {}
		inline ~CreateUsingNew() {}

		inline static T* CreateInstance() { return new T(); }
		inline static void DestroyInstance(T* t) { delete t; }

	private : 
		inline explicit CreateUsingNew(CreateUsingNew const&) {}
		inline CreateUsingNew& operator=(CreateUsingNew const&) { return *this; }
	};	


	template<typename T>
	class CreateUsingStatic {
	protected : 
		inline explicit CreateUsingStatic() {}
		inline ~CreateUsingStatic() {}

		inline static T* CreateInstance() {
			new(t_) T();
			return reinterpret_cast<T*>(t_);
		}
		inline static void DestroyInstance(T* t) { t->~T(); }

	private : 
		static unsigned char t_[];

	private : 
		inline explicit CreateUsingStatic(CreateUsingStatic const&) {}
		inline CreateUsingStatic& operator=(CreateUsingStatic const&) { return *this; }
	};	

	template<typename T>
	unsigned char CreateUsingStatic<T>::t_[sizeof(T)];



	template<typename T>
	class DefaultLifetime {
	protected : 
		inline explicit DefaultLifetime() {}
		inline ~DefaultLifetime() {}

		//	dead reference issues
		inline static void OnDeadReference() { throw std::logic_error("Dead Reference Detected"); }
		inline static void ScheduleForDestruction(void (*pFun)()) { std::atexit(pFun); }

	private : 
		inline explicit DefaultLifetime(DefaultLifetime const&) {}
		inline DefaultLifetime& operator=(DefaultLifetime const&) { return *this; }
	};	



	//	allows recurring singleton
	template<typename T>
	class PhoenixSingleton {
	protected : 
		inline explicit PhoenixSingleton() {}
		inline ~PhoenixSingleton() {}

		//	dead reference issues
		inline static void OnDeadReference() {}
		inline static void ScheduleForDestruction(void (*pFun)()) { std::atexit(pFun); }

	private : 
		inline explicit PhoenixSingleton(PhoenixSingleton const&) {}
		inline PhoenixSingleton& operator=(PhoenixSingleton const&) { return *this; }
	};	

	template<typename T>
	class NoDestruction {
	protected : 
		inline explicit NoDestruction() {}
		inline ~NoDestruction() {}

		//	dead reference issues
		inline static void OnDeadReference() {}
		inline static void ScheduleForDestruction(void (*)()) {}

	private : 
		inline explicit NoDestruction(NoDestruction const&) {}
		inline NoDestruction& operator=(NoDestruction const&) { return *this; }
	};	

	template<typename T, typename CreationPolicy = CreateUsingNew<T>, template <typename> class LifetimePolicy = DefaultLifetime, template <typename> class ThreadingModel = SGT::Threading::SingleThreaded>
	class Singleton : public SGT::Traits::TypeTraits<typename ThreadingModel<T>::VolatileType>, public CreationPolicy, public LifetimePolicy<T>, public ThreadingModel<T> {
	public : 
		
		static RefType Instance();
		
		static void Destroy();
		
		static void Reset(PointerType, void (*pFun)(T*));

	protected : 
		inline explicit Singleton() { Singleton::instance_ = static_cast<PointerType>(this); Singleton::destroyed_ = false; Singleton::pFun_ = 0; }
		inline ~Singleton() { Singleton::instance_ = 0; Singleton::destroyed_ = true; Singleton::pFun_ = 0; }

	private : 
		typedef void (*UserSuppliedDestroy)(T*);

	private : 
		static PointerType instance_;
		static bool destroyed_;
		static UserSuppliedDestroy pFun_;

	private : 
		inline explicit Singleton(Singleton const&) {}
		inline Singleton& operator=(Singleton const&) { return *this; }
	};	//	end of class Singleton

	template<typename T, typename CreationPolicy, template <typename> class LifetimePolicy, template <typename> class ThreadingModel>
	typename Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::RefType Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::Instance() {
		if ( Singleton::instance_ == 0 ) {
			LockThread lock;
			if ( Singleton::instance_ == 0 ) {
				Singleton::pFun_ = 0;
				if ( Singleton::destroyed_ ) {
					OnDeadReference();
					Singleton::destroyed_ = false;
				}
				Singleton::instance_ = CreateInstance();
				try {
					ScheduleForDestruction(Singleton::Destroy);
				} catch(...) {
					DestroyInstance(Singleton::instance_);
				}
			}
		}
		return *(Singleton::instance_);
	}

	template<typename T, typename CreationPolicy, template <typename> class LifetimePolicy, template <typename> class ThreadingModel>
	void Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::Destroy() {
		if ( Singleton::instance_ != 0 ) {
			LockThread lock;
			if ( Singleton::instance_ != 0 ) {
				if (  Singleton::pFun_ != 0 ) {
					Singleton::pFun_(Singleton::instance_);
				} else {
					DestroyInstance(Singleton::instance_);
				}
				Singleton::instance_ = 0;
				Singleton::destroyed_ = true;
			}
		}
	}

	template<typename T, typename CreationPolicy, template <typename> class LifetimePolicy, template <typename> class ThreadingModel>
	void Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::Reset(typename Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::PointerType p, UserSuppliedDestroy pFun) {
		LockThread lock;
		if ( Singleton::instance_ != 0 ) {
			DestroyInstance(Singleton::instance_);
		}
		assert(p);
		Singleton::instance_ = p;
		Singleton::pFun_ = pFun;
		try {
			ScheduleForDestruction(Singleton::Destroy);
		} catch(...) {
			DestroyInstance(Singleton::instance_);
		}
	}

	template<typename T, typename CreationPolicy, template <typename> class LifetimePolicy, template <typename> class ThreadingModel>
	typename Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::PointerType Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::instance_ = 0;
	template<typename T, typename CreationPolicy, template <typename> class LifetimePolicy, template <typename> class ThreadingModel>
	bool Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::destroyed_ = false;
	template<typename T, typename CreationPolicy, template <typename> class LifetimePolicy, template <typename> class ThreadingModel>
	typename Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::UserSuppliedDestroy Singleton<T, CreationPolicy, LifetimePolicy, ThreadingModel>::pFun_ = 0;

};	//	end of namespace SGT

#endif