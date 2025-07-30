module;

#include <flecs.h>

export module gallery;

import types;
import util;

export namespace art {
	
	namespace core {

		using Schedule = flecs::entity_t;

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
			requires requires(T&& experience, art::core::Gallery& gallery)
			{
				{ experience.build(gallery) } -> std::same_as<void>;
			}
			void add_experience(T&& experience)
			{
				// TODO: Get name from type info or meta?
				StringView name = typeid(experience).name();

				if (!m_experiences.contains(name))
				{
					util::Defer timer = util::profile([&name](util::time::Duration<> diff) {
						util::log("Building {} took {}ms", name, diff.count());
					});

					experience.build(*this);
					m_experiences.insert(name);
				}
				else
				{
					// TODO: Send log error event!
				}
			}

			/// <summary>
			/// Add a function to be executed at the specified by the Schedule time of the frame 
			/// The function will run for each entity that has the components specified in the template arguments
			///
			/// </summary>
			/// <param name= "schedule">At which point during the frame the function runs (Ex. OnStart, PreUpdate, OnUpdate...)</param>
			/// <param name= "technique">Function that will run for each entity that mathces</param>
			/// <param name= "name">Optional name for the technique for debug purposes</param>
			/// <param name= "Components">List of components that to match with an entity</param>
			template <typename... Components, typename Tech>
			/*requires requires(Tech technique, Components... components)
			{
				{ technique(std::forward(components...)) } -> std::same_as<void>;
			}*/
			void add_technique(Schedule schedule, Tech&& technique, StringView name = "")
			{
				// TODO: Place them in separate Flows (Or Subflows) based on parameters 
				// graphing them based on mutability, conflicts, etc
				// So we can parallelize them as much as possible and build out the main flow of the engine
				//
				// See Concepts: p1 - Scheduling & Execution
				// m_mainFlow.emplace(technique).name(name.data());

				GetExpo().system<Components...>(name.data()).kind(schedule).each(FLECS_FWD(technique));
			}

			void showtife();
			
			Exposition& GetExpo() { return m_exposition; }

		private:
			HashSet<StringView> m_experiences;

			Exposition m_exposition;
		};


	} // namespace core
} // namespace art