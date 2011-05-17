#pragma once

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>

typedef size_t size_type;
typedef std::pair<std::string,std::string> key_val;
typedef std::vector<key_val> kv_vec;
typedef std::pair<std::string, kv_vec> section;
typedef std::vector<section> sec_vec;
typedef kv_vec::iterator key_val_iter;
typedef kv_vec::const_iterator key_val_citer;

using namespace std;

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS INIReader
{
public:
	INIReader(void);
	virtual ~INIReader(void);
    INIReader(std::istream &stream);
    INIReader(const std::string &path);

    // 加载/保存
    bool LoadFromFile(const std::string &path);
    void LoadFromText(const std::string &text);
    void LoadFromStream(std::istream &stream);
    bool SaveToFile(const std::string &path);
    void SaveToStream(std::ostream &stream);

    // 获取指定section下指定key对应的value
    bool GetValue(const std::string &sec, const std::string &key, std::string &val) const;
    bool GetValue(const std::string &sec, const std::string &key, bool &val) const;
    bool GetValue(const std::string &sec, const std::string &key, short &val) const;
    bool GetValue(const std::string &sec, const std::string &key, unsigned short &val) const;
    bool GetValue(const std::string &sec, const std::string &key, int &val) const;
    bool GetValue(const std::string &sec, const std::string &key, unsigned int &val) const;
    bool GetValue(const std::string &sec, const std::string &key, long &val) const;
    bool GetValue(const std::string &sec, const std::string &key, unsigned long &val) const;
    bool GetValue(const std::string &sec, const std::string &key, float &val) const;
    bool GetValue(const std::string &sec, const std::string &key, double &val) const;

private:
	sec_vec _sv;

	size_type GetSectionSize(void) const;
	section& operator[](size_type pos);
	const section& operator[](size_type pos) const;
	section* GetSection(const std::string &sec);
	const section* GetSection(const std::string &sec) const;
	void append_section(const section &sec);
 };

