#ifndef __THREADS_HPP__
#define __THREADS_HPP__

namespace SGT {

	namespace Threading { 

///////////////////////////////////////////////////////////////////////////
//	class SingleThreaded
///////////////////////////////////////////////////////////////////////////

		//	Defines the locking mechanisim for single threaded model
		//	which is actually empty
		template<typename T>
		class SingleThreaded {
		public : 
			typedef T VolatileType;

		protected : 
			inline explicit SingleThreaded() {}
			inline ~SingleThreaded() {}

		protected : 
			//	Perform thread locks
			class LockThread {
			public : 
				inline explicit LockThread() { SingleThreaded::Lock(); }
	            inline ~LockThread() { SingleThreaded::Unlock(); }

			private : 
				inline explicit LockThread(LockThread const&) {}
				inline LockThread& operator=(LockThread const&) { return *this; }
			};	//	end of class LockThread

		private : 
			//	thread synchronization helps
			friend LockThread;

			inline static void Lock() {}
			inline static void Unlock() {}

		private : 
			inline explicit SingleThreaded(SingleThreaded const&) {}
			inline SingleThreaded& operator=(SingleThreaded const&) { return *this; }
		};	//	end of class SingleThreaded

	};	//	end of namespace Threading

};	//	end of namespace SGT

#endif