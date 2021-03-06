#include "ParseUtilsKey.h"
#include <cctype>
#include "FileUtils.h"
#include "Json/JsonUtils.h"
#include "Game.h"
#include "GameUtils.h"
#include "SFML/SFMLUtils.h"
#include "Utils/Utils.h"

namespace Parser
{
	using namespace rapidjson;
	using namespace Utils;

	AnimationType getAnimationTypeKey(const rapidjson::Value& elem,
		const char* key, AnimationType val)
	{
		if (elem.HasMember(key) == true)
		{
			const auto& keyElem = elem[key];
			if (keyElem.IsString() == true)
			{
				return GameUtils::getAnimationType(keyElem.GetString(), val);
			}
		}
		return val;
	}

	Anchor getAnchorKey(const Value& elem, const char* key, Anchor val)
	{
		if (elem.HasMember(key) == true)
		{
			const auto& keyElem = elem[key];
			if (keyElem.IsString() == true)
			{
				return GameUtils::getAnchor(keyElem.GetString(), val);
			}
			else if (keyElem.IsArray() == true)
			{
				Anchor ret = Anchor::None;
				for (const auto& arrElem : keyElem)
				{
					ret |= GameUtils::getAnchor(getStringVal(arrElem).c_str(), val);
				}
				return ret;
			}
		}
		return val;
	}

	bool getBoolKey(const Value& elem, const char* key, bool val)
	{
		if (elem.HasMember(key) == true
			&& elem[key].IsBool() == true)
		{
			return elem[key].GetBool();
		}
		return val;
	}

	double getDoubleKey(const Value& elem, const char* key, double val)
	{
		if (elem.HasMember(key) == true
			&& elem[key].IsDouble() == true)
		{
			return elem[key].GetDouble();
		}
		return val;
	}

	float getFloatKey(const Value& elem, const char* key, float val)
	{
		if (elem.HasMember(key) == true
			&& elem[key].IsFloat() == true)
		{
			return elem[key].GetFloat();
		}
		return val;
	}

	int getIntKey(const Value& elem, const char* key, int val)
	{
		if (elem.HasMember(key) == true
			&& elem[key].IsInt() == true)
		{
			return elem[key].GetInt();
		}
		return val;
	}

	int64_t getInt64Key(const Value& elem, const char* key, int64_t val)
	{
		if (elem.HasMember(key) == true
			&& elem[key].IsInt64() == true)
		{
			return elem[key].GetInt64();
		}
		return val;
	}

	const char* getStringCharKey(const Value& elem,
		const char* key, const char* val)
	{
		if (elem.HasMember(key) == true
			&& elem[key].IsString() == true)
		{
			return elem[key].GetString();
		}
		return val;
	}

	std::string getStringKey(const Value& elem,
		const char* key, const std::string& val)
	{
		if (elem.HasMember(key) == true)
		{
			return getStringVal(elem[key], val);
		}
		return val;
	}

	std::string_view getStringViewKey(const Value& elem,
		const char* key, const std::string_view val)
	{
		if (elem.HasMember(key) == true)
		{
			return getStringViewVal(elem[key], val);
		}
		return val;
	}

	unsigned getUIntKey(const Value& elem, const char* key, unsigned val)
	{
		if (elem.HasMember(key) == true
			&& elem[key].IsUint() == true)
		{
			return elem[key].GetUint();
		}
		return val;
	}

	uint64_t getUInt64Key(const Value& elem, const char* key, uint64_t val)
	{
		if (elem.HasMember(key) == true
			&& elem[key].IsUint64() == true)
		{
			return elem[key].GetUint64();
		}
		return val;
	}

	std::pair<size_t, size_t> getFramesKey(const Value& elem,
		const char* key, const std::pair<size_t, size_t>& val)
	{
		if (elem.HasMember(key) == true)
		{
			return getFramesVal(elem[key], val);
		}
		return val;
	}

	std::pair<size_t, size_t> getIndexKey(const Value& elem,
		const char* key, const std::pair<size_t, size_t>& val)
	{
		if (elem.HasMember(key) == true)
		{
			return getIndexVal(elem[key], val);
		}
		return val;
	}

	sf::Vector2f getPositionKey(const Value& elem, const char* key,
		const sf::Vector2f& size, const sf::Vector2u& refSize)
	{
		if (elem.HasMember(key) == true)
		{
			return getPositionVal(elem[key], size, refSize);
		}
		return {};
	}

	sf::IntRect getIntRectKey(const Value& elem,
		const char* key, const sf::IntRect& val)
	{
		if (elem.HasMember(key) == true)
		{
			return getIntRectVal(elem[key], val);
		}
		return val;
	}

	sf::FloatRect getFloatRectKey(const Value& elem,
		const char* key, const sf::FloatRect& val)
	{
		if (elem.HasMember(key) == true)
		{
			return getFloatRectVal(elem[key], val);
		}
		return val;
	}

	sf::Color getColorKey(const Value& elem, const char* key, const sf::Color& val)
	{
		if (elem.HasMember(key) == true)
		{
			return getColorVal(elem[key], val);
		}
		return val;
	}

	sf::Time getTimeKey(const Value& elem, const char* key, const sf::Time& val)
	{
		if (elem.HasMember(key) == true)
		{
			return getTimeVal(elem[key], val);
		}
		return val;
	}

	std::vector<std::string> getStringVectorKey(const Value& elem, const char* key)
	{
		std::vector<std::string> vec;
		if (elem.HasMember(key) == true)
		{
			const auto& elemVal = elem[key];
			if (elemVal.IsArray() == true)
			{
				for (const auto& val : elemVal)
				{
					vec.push_back(JsonUtils::toString(val));
				}
			}
			else if (elemVal.IsString() == true)
			{
				vec.push_back({ elemVal.GetString(), elemVal.GetStringLength() });
			}
		}
		return vec;
	}

	IgnoreResource getIgnoreResourceKey(const Value& elem,
		const char* key, IgnoreResource val)
	{
		if (elem.HasMember(key) == true)
		{
			return getIgnoreResourceVal(elem[key], val);
		}
		return val;
	}

	InputEvent getInputEventKey(const Value& elem,
		const char* key, InputEvent val)
	{
		if (elem.HasMember(key) == true)
		{
			return getInputEventVal(elem[key], val);
		}
		return val;
	}

	size_t getInventoryItemIndexKey(const Value& elem,
		const char* key, PlayerInventory inv)
	{
		if (elem.HasMember(key) == true)
		{
			return getInventoryItemIndexVal(elem[key], inv);
		}
		return 0;
	}

	InventoryPosition getInventoryPositionKey(const Value& elem,
		const char* key, InventoryPosition val)
	{
		if (elem.HasMember(key) == true)
		{
			return getInventoryPositionVal(elem[key], val);
		}
		return val;
	}

	LightSource getLightSourceKey(const rapidjson::Value& elem,
		const char* key, LightSource val)
	{
		if (elem.HasMember(key) == true)
		{
			return getLightSourceVal(elem[key], val);
		}
		return val;
	}

	ItemCoordInventory getItemCoordInventoryKey(const Value& elem, const char* key)
	{
		if (elem.HasMember(key) == true)
		{
			return getItemCoordInventoryVal(elem[key]);
		}
		return{};
	}

	ItemLocation getItemLocationKey(const Value& elem, const char* key)
	{
		if (elem.HasMember(key) == true)
		{
			return getItemLocationVal(elem[key]);
		}
		return{};
	}

	ItemXY getItemXYKey(const Value& elem, const char* key, const ItemXY& val)
	{
		if (elem.HasMember(key) == true)
		{
			return getItemXYVal(elem[key], val);
		}
		return val;
	}

	PlayerDirection getPlayerDirectionKey(const Value& elem,
		const char* key, PlayerDirection val)
	{
		if (elem.HasMember(key) == true)
		{
			const auto& keyElem = elem[key];
			if (keyElem.IsString() == true)
			{
				return GameUtils::getPlayerDirection(keyElem.GetString(), val);
			}
		}
		return val;
	}

	PlayerInventory getPlayerInventoryKey(const Value& elem,
		const char* key, PlayerInventory val)
	{
		if (elem.HasMember(key) == true)
		{
			return getPlayerInventoryVal(elem[key], val);
		}
		return val;
	}

	PlayerItemMount getPlayerItemMountKey(const Value& elem,
		const char* key, PlayerItemMount val)
	{
		if (elem.HasMember(key) == true)
		{
			const auto& keyElem = elem[key];
			if (keyElem.IsString() == true)
			{
				return GameUtils::getPlayerItemMount(keyElem.GetString(), val);
			}
		}
		return val;
	}

	PlayerAnimation getPlayerAnimationKey(const Value& elem,
		const char* key, PlayerAnimation val)
	{
		if (elem.HasMember(key) == true)
		{
			const auto& keyElem = elem[key];
			if (keyElem.IsString() == true)
			{
				return GameUtils::getPlayerAnimation(
					{ keyElem.GetString(), keyElem.GetStringLength() }, val);
			}
		}
		return val;
	}

	PlayerStatus getPlayerStatusKey(const Value& elem,
		const char* key, PlayerStatus val)
	{
		if (elem.HasMember(key) == true)
		{
			const auto& keyElem = elem[key];
			if (keyElem.IsString() == true)
			{
				return GameUtils::getPlayerStatus(
					{ keyElem.GetString(), keyElem.GetStringLength() }, val);
			}
		}
		return val;
	}

	ReplaceVars getReplaceVarsKey(const Value& elem, const char* key, ReplaceVars val)
	{
		if (elem.HasMember(key) == true)
		{
			return getReplaceVarsVal(elem[key]);
		}
		return val;
	}

	Variable getVariableKey(const Value& elem, const char* key)
	{
		if (elem.HasMember(key) == true)
		{
			return getVariableVal(elem[key]);
		}
		return Variable();
	}

	VarOrPredicate getVarOrPredicateKey(Game& game, const Value& elem, const char* key)
	{
		if (elem.HasMember(key) == true)
		{
			return getVarOrPredicateVal(game, elem[key]);
		}
		return VarOrPredicate();
	}
}
