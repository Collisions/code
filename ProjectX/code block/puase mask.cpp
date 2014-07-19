auto actionManager = Director::getInstance()->getActioinManager();
if (flag)
{
	auto lay = this->getChildByTag(99);
	actionManager->resumeTarget(lay);
	flag = false;
	
	auto mask = this->getChildByTag(1);
	mask->removeFromParent();
} else {
	actionManager->pauseAllRunningAction();
	flag = true;
	
	auto size = Director::getInstance()->getVisibleSize();
		
	auto mask = LayerColor::create(Color4B::RED, size.width, size.height);
	mask-setAnchorPoint(Point(0, 0));
	this->addChild(mask);
	mask->setOpacity(100);
	mask->setTag(1);
}