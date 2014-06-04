//std::vector
std::vector<int> vec;
for (int i = 0; i < 10; i++)
{
	vec.push_back(i);
}
for (int i = 0; i < vec.size(); i++)
{
	log("vector===>%d", vec[i]);
}

//cocos2d::Vector
Vector<Node*> vet;
for (int i = 0; i < 10; i++)
{
	auto lay = Layer::create();
	lay->setTag(i);
	vet.pushBack(lay);
}
for (auto lay: vet)
{
	log("Vector===>%d", lay->getTag());
}

//cocos2d::Map
Map<std::string, Node*> map;
for (int i = 0; i < 10; i++)
{
	auto lay = Layer::create();
	lay->setTag(i);
	map.insert("m"+i, lay);
}
for (auto key : map.keys())
{
	log("Map===>%d", map.at(key)->getTag());
}