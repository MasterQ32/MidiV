#include "mcctarget.hpp"
#include "debug.hpp"
#include "utils.hpp"

MCCTarget::MCCTarget() : type(Unknown), channel(0xFF), scale(1.0), value(0.0), index(0)
{
	// identity mapping
	mapping.low = 0.0;
	mapping.high = 1.0;
}

MCCTarget MCCTarget::load(nlohmann::json const & override)
{
	auto const src = Utils::get(override, "source", std::string(""));

	MCCTarget target;
	target.channel = uint8_t(Utils::get(override, "channel", 0xFF));
	target.priority = Utils::get(override, "priority", 0.0);
    target.scale = Utils::get(override, "scale", 1.0);
	target.integrate = Utils::get(override, "integrate", false);
	target.sum_value = 0.0;

	if(override.find("map") != override.end())
	{
		target.mapping.low = override["map"][0].get<double>();
		target.mapping.high = override["map"][1].get<double>();
	}

	if((src == "value") || ((src == "") && override.find("value") != override.end()))
	{
		target.type = Fixed;
		target.fixed = override["value"].get<double>();
	}
	else if((src == "cc") || ((src == "") && override.find("cc") != override.end()))
	{
		target.type = CC;
		target.index = uint8_t(override["cc"].get<int>());
	}
	else if((src == "note") || ((src == "") && override.find("note") != override.end()))
	{
		target.type = Note;
		target.index = uint8_t(override["note"].get<int>());
		if(target.channel == 0xFF)
		{
			target.channel = 0;
			Log() << "Note binding requires a channel, defaulting to channel " << (int)target.channel << "!";
		}
	}
	else if(src == "pitch")
	{
		target.type = Pitch;
	}
	else
	{
		target.type = Unknown;
		Log() << "Uniform specifier must have either source, cc or value assigned!";
	}
	return target;
}

// implemented in midiv.cpp for additional fuckup
// void MCCTarget::update(double deltaTime)
