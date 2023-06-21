#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>

enum class StatusType { TEXT = 1, IMAGE, VIDEO };

class Status
{
	time_t date;
	std::string text;

public:
	Status(const std::string _text) :
		text(_text)
	{
		date = time(&date);
	}
	
	Status(const Status& s) = delete;

	virtual ~Status() = default;

	virtual Status& operator=(const Status& s)
	{
		date = s.date;
		text = s.text;
		return *this;
	}

	virtual bool operator== (Status*& s) const;
	virtual bool operator!= (Status*& s) const;

	virtual void printStatus() const;
	friend void addStatus(std::vector<Status*>& arr, Status* stat);
	friend void printStatuses(const std::vector<Status*>& board, int numOfStatusToPrint);

	const std::string& getText()const
	{
		return text;
	}

	const time_t& getDate()const
	{
		return date;
	}

	void setDate(time_t& _date)
	{
		date = _date;
	}
};

class PicStatus : public Status
{
	std::string picName;

public:
	PicStatus(const std::string _text, const std::string _fileName):Status(_text), picName(_fileName){}

	PicStatus(const PicStatus& s) = delete;

	virtual ~PicStatus() = default;

	virtual PicStatus& operator=(const PicStatus& s)
	{
		this->Status::operator=(s);
		picName = s.picName;
		return *this;
	}

	virtual bool operator== (Status*& s) const;
	virtual bool operator!= (Status*& s) const;

	virtual void printStatus() const;

	const std::string& getPicName()const
	{
		return picName;
	}
};

class VideoStatus : public Status
{
	std::string videoName;

public:
	VideoStatus(const std::string _text, const std::string _videoName) :Status(_text), videoName(_videoName) {}

	VideoStatus(const VideoStatus& s) = delete;

	virtual ~VideoStatus() = default;

	virtual VideoStatus& operator=(const VideoStatus& s)
	{
		this->Status::operator=(s);
		videoName = s.videoName;
		return *this;
	}

	virtual bool operator== (Status*& s) const;
	virtual bool operator!= (Status*& s) const;

	virtual void printStatus() const;

	const std::string& getVideoName()const
	{
		return videoName;
	}
};

