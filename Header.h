#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "pugixml.hpp"

class Style
{
private:
	std::string id;
	std::string fontName;
	size_t fontSize;
public:
	Style(std :: string styleId, pugi::xml_document& stylesDoc)
	{
		id = styleId;
		std::string query = "//w:style[@w:styleId='" + id + "']";
		pugi::xpath_node style_in_styles_xml = stylesDoc.select_node(query.c_str());
		if (!style_in_styles_xml)
		{
			std::cerr << "Error: style not found\n";
			return;
		}
		pugi::xml_node node = style_in_styles_xml.node();
		pugi::xml_node fontNode = node.child("w:rPr").child("w:rFonts");
		this->fontName = fontNode.attribute("w:ascii").value();

		pugi::xml_node sizeNode = node.child("w:rPr").child("w:sz");
		std::string sizeStr = sizeNode.attribute("w:val").value();
		if (!sizeStr.empty())
		{
			this->fontSize = std::stoull(sizeStr) / 2;

		}
		else this->fontSize = 0;
	}
	~Style()=default;
	auto getFontName()const
	{
		return fontName;
	}
	auto getFontSize()const
	{
		return fontSize;
	}
};
class Paragraph
{
	private: 
	std::string styleId;
	std::string label;
	bool isEmpty=false;
public:
	Paragraph(pugi::xml_node paragraphNode)
	{
		auto styleNode = paragraphNode.child("w:pPr").child("w:pStyle");
		this->styleId = styleNode ? styleNode.attribute("w:val").value() : "Normal";

		auto textNode = paragraphNode.child("w:r").child("w:t");
		std::string rawText = textNode.text().get();
		if (rawText.empty())
		{
			this->isEmpty = true;
		}
		else
			this->isEmpty = false;
		if (rawText.length() > 30)
		{
			this->label = rawText.substr(0, 30) + "...\n";
		}
		else label = rawText;
		
	}

};
class DocxChecker
{
private:
	std::vector<Paragraph> paragraphs;
	pugi::xml_document stylesDoc;
public:
	DocxChecker();
	~DocxChecker() = default;
	auto load(std::string dir)
	{
		
	}
	auto check(std::string expectedFont, std::string expectedSize);
};
class Logger
{
	std::vector<Paragraph> errors;
public:
	void logError(std::string label, std::string message)
	{
		
	}
};