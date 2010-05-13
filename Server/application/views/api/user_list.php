<?php echo '<?xml version="1.0" encoding="utf-8"?>'; ?>

<users><?php if (count($list)>0) foreach($list as $user){ ?>
	
	<user login="<?php echo $user->username ; ?>" description="<![CDATA <?php echo $user->description; ?> ]]>" last_activity="<?php echo $user->last_activity ; ?>" <?php if (isset($avatar)) echo 'avatar="'.$avatar.'" '; ?> />
	<?php } ?>

</users>