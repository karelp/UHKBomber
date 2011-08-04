#ifndef INIREADER_H
#define INIREADER_H

#include <boost/lexical_cast.hpp>
#include <map>
#include <string>

/**
 * @brief
 * A class for reading INI files.
 * 
 * The class can be used for parsing INI configuration files.
 * There are two basic use cases - SAX-like mode that is
 * provided using the onNewSection and onEntry callbacks, and
 * full-parse mode that parses the whole file and then allows
 * picking the concrete items.
 * 
 * @remarks
 * The class has been taken from the OpenLieroX project and edited to meet purposes
 * of this project. Original code by Albert Zeyer.
 */
class IniReader {
public:
	typedef std::map<std::string, int> KeywordList;


	/**
	 * @brief
	 * Construct the reader and initialize it with an INI file name.
	 * 
	 * @param filename
	 * Path to the INI file to parse.
	 * 
	 * @param keywords
	 * Keywords and their corresponding numerical values, useful for named constants.
	 * 
	 * Initializes the reader and prepares the parser, no parsing is run though. You
	 * have to explicitly call the parse() method to process the file.
	 * 
	 * @see
	 * IniReader::parse
	 */
	IniReader(const std::string& filename, KeywordList& keywords = IniReader::DefaultKeywords);

	virtual ~IniReader() {}
	
	/**
	 * @brief
	 * Parses the INI file.
	 * 
	 * @returns
	 * True if (a) the given file is syntactically correct and (b) none of the callbacks
	 * (onNewSection, onEntry) returned false.
	 *
	 * Parses the INI file sequentially while calling the onNewSection and onEntry callbacks
	 * when appropriate. The sections and entries are simultaneously stored into an internal
	 * structure and can be later retrieved using read* methods.
	 * 
	 * @remarks
	 * Parsing stops immediatelly when any of the callbacks returns false.
	 * There are no attempts to continue parsing after a syntactical error has encountered.
	 * 
	 * @see
	 * IniReader::onNewSection | IniReader::onEntry
	 */
	bool parse();

	
	/**
	 * @brief
	 * This callback is called when a new section is parsed. Override
	 * this method in your subclass to add custom logic.
	 * 
	 * @param section
	 * Name of the new section.
	 * 
	 * @returns
	 * Should return true if everything went OK, false if the parsing should
	 * stop imediatelly.
	 * 
	 * @see
	 * IniReader::parse
	 */
	virtual bool onNewSection (const std::string& section) { return true; }

	/**
	 * @brief
	 * This callback is called when a new entry is parsed. Override
	 * this method in your subclass to add custom logic.
	 * 
	 * @param section
	 * The section this entry belongs to.
	 * 
	 * @param propname
	 * Name of the entry.
	 * 
	 * @param value
	 * Value of the entry.
	 * 
	 * @returns
	 * Should return true if everything went OK, false if the parsing should
	 * stop imediatelly.
	 * 
	 * @see
	 * IniReader::parse
	 */
	virtual bool onEntry(const std::string& section, const std::string& propname, const std::string& value) { return true; }

	
	/**
	 * @brief
	 * Read a value from the INI file.
	 * 
	 * @param section
	 * Section of the key containing the requested value.
	 * 
	 * @param key
	 * Key containing the requested value.
	 * 
	 * @param value
	 * The requested value (output parameter).
	 * 
	 * @param defaultv
	 * Default value to be used when the key s not found.
	 * 
	 * @returns
	 * True if the key is found and the value has been successfully converted to C++ type.
	 *
	 * Use the read function to read a data type from the INI file, such as:
	 * int value = 0;
	 * ini.read("MySection", "MyKey", value, 42);
	 * Success or failure can be checked using the return value.
	 * 
	 * @see
	 * IniReader::readKeyword
	 */
	template <typename T>
	bool read(const std::string& section, const std::string& key, T& value, const T& defaultv) const
	{
		std::string string;
		value = defaultv;

		if (!getString(section, key, string))
			return false;

		try {
			value = boost::lexical_cast<T>(string);
		} catch (boost::bad_lexical_cast& ) {
			value = defaultv;
			return false;
		}

		return true;
	}

	/**
	 * @brief
	 * Reads a keyword from the INI file and converts it to a numerical value.
	 * 
	 * @param section
	 * Section of the key containing the requested value.
	 * 
	 * @param key
	 * Key containing the requested value.
	 * 
	 * @param value
	 * The requested value (output parameter).
	 * 
	 * @param defaultv
	 * Default value to be used when the key s not found.
	 * 
	 * @returns
	 * True if the key is found and the value has been successfully converted to a numeric/boolean type.
	 * 
	 * Use this function to read numerical constants from the INI file. The constants can be specified
	 * in constructor and default to (true => 1, false => 0).
	 * 
	 * @remarks
	 * The template parameter must be an integral or boolean type.
	 * 
	 * @see
	 * IniReader::read | IniReader::IniReader
	 */
	template <typename IntegralT>
	bool readKeyword(const std::string& section, const std::string& key, IntegralT& value, IntegralT defaultv) const
	{
		std::string string;
		value = defaultv;

		if (!getString(section, key, string))
			return false;

		// Try and find a keyword with matching keys
		KeywordList::const_iterator f = m_keywords.find(string);
		if(f != m_keywords.end()) {
			*value = f->second;
			return true;
		}

		return false;
	}

	// Properties

	const std::string& getFileName() const { return m_filename; }

	// Constants

	static KeywordList DefaultKeywords;
protected:
	std::string m_filename;
	KeywordList& m_keywords;

public:
	typedef std::map<std::string, std::string> Section;
	typedef std::map<std::string, Section> SectionMap;

private:
	/**
	 * @brief
	 * Associative array of sections and their contents.
	 */
	SectionMap m_sections;

	/**
	 * @brief
	 * Pointer to current section in m_sections, used as a temporary while parsing.
	 */
	Section *m_curSection;

private:
	/**
	 * @brief
	 * Helper method for the read* methods above. Gets a value as string
	 * based on section and key.
	 * 
	 * @param section
	 * Section to look in.
	 * 
	 * @param key
	 * Key to find.
	 * 
	 * @param string
	 * Resulting value (output).
	 * 
	 * @returns
	 * True if the key was found, false otherwise.
	 */
	bool getString(const std::string& section, const std::string& key, std::string& string) const;

	// Parser states

	void newSection(const std::string& name);
	void newEntryInSection(const std::string& name, const std::string& value);
	
};

#endif

