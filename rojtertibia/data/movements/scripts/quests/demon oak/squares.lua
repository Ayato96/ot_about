local voices = {
	'Release me and you will be rewarded greatefully!',
	'What is this? Demon Legs lying here? Someone might have lost them!',
	'I\'m trapped, come here and free me fast!!',
	'I can bring your beloved back from the dead, just release me!',
	'What a nice shiny golden armor. Come to me and you can have it!',
	'Find a way in here and release me! Pleeeease hurry!',
	'You can have my demon set, if you help me get out of here!'
}

function onStepIn(creature, item, position, fromPosition)
	local player = creature:getPlayer()
	if not player then
		return true
	end

	local status = math.max(player:getStorageValue(Storage.DemonOak.Squares), 0)
	if item.uid - 9000 == status + 1 then
		player:setStorageValue(Storage.DemonOak.Squares, status + 1)
		player:say(voices[math.random(#voices)], TALKTYPE_MONSTER_YELL, false, player, DEMON_OAK_POSITION)
	end
	return true
end