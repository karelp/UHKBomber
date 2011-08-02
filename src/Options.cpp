#include <fstream>
#include "IniReader.h"
#include "Options.h"

/**
 * @brief
 * A custom specialization of IniReader to read options file.
 * 
 * @see
 * IniReader
 */
class OptionsReader : public IniReader  {
	Options& m_options;

public:
	OptionsReader(const std::string& fileName, Options& options) : IniReader(fileName), m_options(options) { }

	bool onEntry(const std::string& section, const std::string& propname, const std::string& value) override
	{
		std::string fullPath = section + "." + propname;
		try  {
			m_options.m_fields[fullPath]->fromString(value);
		} catch (boost::bad_lexical_cast& )  {
			// TODO: logging system
			// TODO: return false here?
		}

		return true;
	}
};

bool Options::loadFromFile(const std::string& fileName)
{
	OptionsReader ini(fileName, *this);

	if (!ini.parse())
		return false;

	return true;
}

/**
 * @brief
 * Helper function for Options::saveToFile that splits a field name
 * to section and key.
 * 
 * @param fullPath
 * Full field name (i.e. "video.screenWidth")
 * 
 * @returns
 * A pair of strings, first one contains the section, second one INI key.
 * 
 * Helper function that splits a string like "video.screenWidth" to
 * "video" and "screenWidth". The first part is used as a section
 * and the second part as a key for the INI file. In case there are
 * multiple dots, the last one is taken as a section delimiter.
 * If there is no delimiter present, the section is taken from
 * Options::defaultSectionName and the whole input string is copied
 * into the key part.
 * 
 * @see
 * Options::saveToFile | Options::defaultSectionName
 */
static std::pair<std::string, std::string> splitToSectionAndKey(const std::string& fullPath)
{
	const std::string::size_type dotPos = fullPath.rfind('.');
	if (dotPos == std::string::npos)
		return std::make_pair(Options::defaultSectionName, fullPath);

	return std::make_pair(fullPath.substr(0, dotPos), fullPath.substr(dotPos + 1));
}

bool Options::saveToFile(const std::string& fileName)
{
	std::ofstream fp;
	fp.open(fileName);
	if (!fp.is_open())  {
		return false;
	}

	std::string currentSection = Options::defaultSectionName;

	for (auto it = m_fields.begin(); it != m_fields.end() && fp.good(); ++it)  {
		std::pair<std::string, std::string> sectionAndKey = splitToSectionAndKey(it->first);
		if (sectionAndKey.first != currentSection)  {
			currentSection = sectionAndKey.first;
			fp << "\n[" << currentSection << "]\n";
		}

		fp << sectionAndKey.second << " = " << it->second->toString() << "\n";
	}

	if (!fp.good())  {
		fp.close();
		return false;
	}

	fp.close();
	return true;
}
