module;

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

			HashSet<StringView> m_experiences;
		private:
		};

		template<typename T>
		concept Experience = requires(T&& experience, art::core::Gallery& gallery)
		{
			{ experience.build(gallery) } -> std::same_as<void>;
			{ experience.get_name() } -> std::convertible_to<StringView>;
		};

		void add_experience(Gallery& gallery, Experience auto&& experience)
		{
			// TODO: Get name from type info?
			StringView name = experience.get_name();

			if (!gallery.m_experiences.contains(name))
			{
				experience.build(gallery);
				gallery.m_experiences.insert(name);
			}
			else
			{
				// TODO: Send log error event!
			}
		}
	} // namespace core
} // namespace art