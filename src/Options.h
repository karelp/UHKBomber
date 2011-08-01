#ifndef OPTIONS_H
#define OPTIONS_H

#include <map>
#include <boost/lexical_cast.hpp>

/**
 * @brief
 * A common ancestor for all option fields.
 * 
 * This ancestor serves the purpose of an easier loading and saving of property fields.
 */
class OptionsFieldBase  {
private:
	std::string m_name;
public:
	/**
	 * @brief
	 * Converts the string to the underlying data type and sets the option.
	 * 
	 * @param str
	 * The string parameter to convert to the option
	 * 
	 * @remarks
	 * Used when loading options.
	 * 
	 * @see
	 * Options::loadFromFile
	 */
	virtual void fromString(const std::string& str) = 0;

	/**
	 * @brief
	 * Convert the option value to a string.
	 * 
	 * @returns
	 * String value of the option.
	 * 
	 * @remarks
	 * Used when saving options.
	 * 
	 * @see
	 * Options::saveToFile
	 */
	virtual std::string toString() const = 0;

	// Properties

	virtual const std::string& name() const { return m_name; }
	virtual std::string& name() { return m_name; }

	virtual ~OptionsFieldBase() {}
};

/**
 * @brief
 * A single option in Options.
 * 
 * @param T
 * C++ type of the option.
 * 
 * This class is used as a wrapper around the raw types. This will later allow an easy registration
 * of callbacks and events in case they are required.
 */
template <typename T>
class OptionsField : public OptionsFieldBase {
private:
	T m_value;

public:
	OptionsField() : m_value() { }
	OptionsField(const T& val) : m_value(val) { }
	operator T() { return m_value; }
	OptionsField& operator= (const T& val) { m_value = val; }

	void fromString(const std::string& str) override
	{
		m_value = boost::lexical_cast<T>(str);
	}

	std::string toString() const override
	{
		return boost::lexical_cast<std::string>(m_value);
	}
};

/**
 * @brief
 * Class for holding global game options.
 * 
 * Global game settings such as resolution, music settings etc. are stored here.
 * These options can be accessed using Game::options() method.
 * 
 * @remarks
 * Please keep this class as small as possible and do not pollute it with useless
 * options.
 * 
 * @see
 * Game::options
 */
class Options  {
private:
	friend class Game;

	std::map<std::string, OptionsFieldBase*> m_fields;

#define regField(field, defValue) registerField(field, #field, defValue)
	
	/**
	 * @brief
	 * Default constructor providing usable defaults.
	 * 
	 * In case loading of the options from an external file fails, this constructor
	 * should provide viable defaults for all values.
	 */
	Options()
	{
		regField(video.screenWidth, 640);
		regField(video.screenHeight, 480);
		regField(video.fullscreen, false);

		regField(audio.musicOn, true);
		regField(audio.soundsOn, true);
	}

#undef regField

	/**
	 * @brief
	 * Registers an options field so that it is available for loading/saving.
	 * 
	 * @param field
	 * The field to register.
	 * 
	 * @param name
	 * Fully qualified field name.
	 *
	 * @param defaultValue
	 * Default value for the option.
	 * 
	 * Adds the field to m_fields which is later used when loading/saving options.
	 *
	 * @remarks
	 * Do not use directly, use the regField macro above to save typing.
	 * 
	 * @see
	 * Options::loadFromFile | Options::saveToFile | m_fields
	 */
	template <typename T>
	void registerField(OptionsField<T>& field, const std::string& name, const T& defaultValue)
	{
		field = defaultValue;
		m_fields[name] = &field;
	}

	/**
	 * @brief
	 * Load options from an external file.
	 * 
	 * @returns
	 * True if the options were successfully loaded.
	 *
	 * @param fileName
	 * The file name to load. Can be an absolute or relative path.
	 * 
	 * Loads options from the specified file. If this function is called multiple times, 
	 * the values are overwritten. Can be called only from Game class.
	 */
	bool loadFromFile(const std::string& fileName);

public:
	/**
	 * @brief
	 * Saves options to the specified file.
	 * 
	 * @param fileName
	 * Path to the file.
	 * 
	 * @returns
	 * True if the saving was successful, false otherwise.
	 * 
	 * Saves all options to the specified file. The target file gets overwritten
	 * or created if it does not exist.
	 */
	bool saveToFile(const std::string& fileName);

public:
	struct  {
		OptionsField<int> screenWidth;
		OptionsField<int> screenHeight;
		OptionsField<bool> fullscreen;
	} video;

	struct  {
		OptionsField<bool> musicOn;
		OptionsField<bool> soundsOn;
	} audio;
};

#endif