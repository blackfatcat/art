module;

#include <flecs.h>

#include <functional> // std::bind

export module gallery;

import types;
import util;

export namespace art {
	
	namespace core {

		using Schedule = flecs::entity_t;

		struct ExpoState { bool open = true; };

		class Gallery
		{
		public:
			Gallery();
			~Gallery();

			/// <summary>
			/// A type qualifies to be an Experience, if 
			/// it has a function called 'build' that takes in a Gallery reference
			/// in order to add its functionality to it
			///
			/// </summary>
			/// <param name="experience:">instance of an Experience to be built into the Gallery</param>
			template<typename T>
			requires requires(T* experience, art::core::Gallery& gallery, void* self)
			{
				{ T::create() } -> std::same_as<T*>;
				{ T::destroy(self) } -> std::same_as<void>;
				{ experience->build(gallery) } -> std::same_as<void>;
			}
			void create_experience()
			{
				T* experience = T::create();

				// TODO: Get name from type info or meta?
				StringView name = typeid(experience).name();

				if (!m_experiences.contains(name))
				{
					util::Defer timer = util::profile([&name](util::time::Duration<> diff) {
						util::log(std::source_location::current(), "Building {} took {}ms", name, diff.count());
					});

					experience->build(*this);

					// Funny note: .insert here will not work as it will try to directly copy the function object into the map
					// which *I think* will not work as at no point can it cast that copy into the underlying function type/
					// Creating it in-place, however, allows for the std::functoin constructor to be called from the passed in function object
					m_destroyers.emplace(name, std::bind(&T::destroy, (void*)experience));
					m_experiences.emplace(name, (void*)experience);
				}
				else
				{
					// TODO: Send log error event!
					util::error(std::source_location::current(), "Error building {}", name);
				}
			}

			/// <summary>
			/// Add a function to be executed at the specified by the Schedule time of the frame 
			/// The function will run for each entity that has the components specified in the template arguments
			///
			/// </summary>
			/// <param name= "schedule">At which point during the frame should the function run (Ex. OnStart, PreUpdate, OnUpdate...)</param>
			/// <param name= "technique">Function that will run for each entity that mathces the components list</param>
			/// <param name= "name">Optional name for the technique for debug purposes</param>
			/// <param name= "Components">List of components that to match with an entity</param>
			template <typename... Components, typename Tech>
			void add_technique(Schedule schedule, Tech&& technique, StringView name = "")
			{
				// TODO: Place them in separate Flows (Or Subflows) based on parameters 
				// graphing them based on mutability, conflicts, etc
				// So we can parallelize them as much as possible and build out the main flow of the engine
				//
				// See Concepts: p1 - Scheduling & Execution

				GetExpo().system<Components...>(name.data()).kind(schedule).each(FLECS_FWD(technique));
			}

			void showtife();
			
			Exposition& GetExpo() { return m_exposition; }

		private:
			HashMap<StringView, Functor<void(void*)>> m_destroyers;
			HashMap<StringView, void*> m_experiences;

			Exposition m_exposition;
		};


	} // namespace core
} // namespace art