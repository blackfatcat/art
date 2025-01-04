module;

#include "taskflow/taskflow.hpp";

export module core;

import std;
import types;

export namespace art {
	
	namespace core {

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
			/// <param name="experience">Experience to be built into the Gallery</param>
			template<typename T>
			requires requires(T&& experience, art::core::Gallery& gallery)
			{
				{ experience.build(gallery) } -> std::same_as<void>;
			}
			void add_experience(T&& experience)
			{
				// TODO: Get name from type info?
				StringView name = typeid(experience).name();

				if (!m_experiences.contains(name))
				{
					experience.build(*this);
					m_experiences.insert(name);
				}
				else
				{
					// TODO: Send log error event!
				}
			}

			template <typename Tech>
			void add_technique(Tech technique, StringView name = "")
			{
				m_mainFlow.emplace(technique).name(name.data());
			}

			void showtife();

		private:
			HashSet<StringView> m_experiences;
			tf::Taskflow m_mainFlow;
			tf::Executor m_runner;
		};


	} // namespace core
} // namespace art