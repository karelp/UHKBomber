#include <fstream>
#include "IniReader.h"

IniReader::KeywordList IniReader::DefaultKeywords;


IniReader::IniReader(const std::string& filename, KeywordList& keywords) : m_filename(filename), m_keywords(keywords) {
	// Initialize basic keywords here
	if (IniReader::DefaultKeywords.empty())  {
		(IniReader::DefaultKeywords)["true"] = true;
		(IniReader::DefaultKeywords)["false"] = false;
	}
}

bool IniReader::parse() {
	std::ifstream f;
	f.open(m_filename);
	if(!f.is_open())
		return false;

	bool res = true;
	enum ParseState {
		S_DEFAULT, 
		S_IGNORERESTLINE, 
		S_PROPNAME, 
		S_PROPVALUE, 
		S_SECTION 
	};

	ParseState state = S_DEFAULT;
	std::string propname, section, value;
	
	while(f.good()) {
		unsigned char c = 0;
		f >> c;
		if(!f.good()) break;

		if(c == '\r') continue; // ignore this
		
		switch (state)  {
		case S_DEFAULT:
			if(c >= 128) break; // just ignore unicode-stuff when we are in this state (UTF8 bytes at beginning are also handled by this)
			else if(isspace((unsigned char)c)) break; // ignore spaces and newlines
			else if(c == '#') { state = S_IGNORERESTLINE; /* this is a comment */ break; }
			else if(c == '[') { state = S_SECTION; section = ""; break; }
			else if(c == '=') {
				//warnings << "WARNING: \"=\" is not allowed as the first character in a line of " << m_filename << endl;
				break; /* ignore */ }
			else { state = S_PROPNAME; propname = c; break; }

		case S_SECTION:
			if(c == ']') {
				if (!onNewSection(section))  { res = false; goto parseCleanup; }
				state = S_DEFAULT; newSection(section); break; }
			else if(c == '\n') {
				//warnings << "WARNING: section-name \"" << section << "\" of " << m_filename << " is not closed correctly" << endl;
				state = S_DEFAULT; break; }
			else if(isspace((unsigned char)c)) {
				//warnings << "WARNING: section-name \"" << section << "\" of " << m_filename << " contains a space" << endl;
				break; /* ignore */ }
			else { section += c; break; }
			
		case S_PROPNAME:
			if(c == '\n') {
				//warnings << "WARNING: property \"" << propname << "\" of " << m_filename << " incomplete" << endl;
				state = S_DEFAULT; break; }
			else if(isspace(c)) break; // just ignore spaces
			else if(c == '=') { state = S_PROPVALUE; value = ""; break; }
			else { propname += c; break; }
			
		case S_PROPVALUE:
			if(c == '\n' || c == '#') { 
				if (!onEntry(section, propname, value) ) { res = false; goto parseCleanup; }
				newEntryInSection(propname, value);
				if(c == '#') state = S_IGNORERESTLINE; else state = S_DEFAULT;
				break; }
			else if(isspace((unsigned char)c) && value.empty()) break; // ignore heading spaces
			else { value += c; break; }
		
		case S_IGNORERESTLINE:
			if(c == '\n') state = S_DEFAULT;
			break; // ignore everything
		}
	}

	// In case the endline is missing at the end of file, finish the parsing of the last line
	if (state == S_PROPVALUE)  {
		if (!onEntry(section, propname, value) ) { res = false; goto parseCleanup; }
		newEntryInSection(propname, value);
	}
	
parseCleanup:
	f.close();
	
	return res;
}

void IniReader::newSection(const std::string& name)
{
	m_curSection = &m_sections[name];
}

void IniReader::newEntryInSection(const std::string& name, const std::string& value)
{
	if (!m_curSection)  {
		//warnings << "Cannot add item " << name << " to any section, because the current section is unset" << endl;
		return;
	}

	(*m_curSection)[name] = value;
}

bool IniReader::getString(const std::string& section, const std::string& key, std::string& string) const
{
	// Get the section
	SectionMap::const_iterator sect = m_sections.find(section);
	if (sect == m_sections.end())
		return false;

	// Get the key=value pair
	Section::const_iterator item = sect->second.find(key);
	if (item == sect->second.end())
		return false;

	string = item->second;
	return true;
}
