<?php echo '<?xml version="1.0" encoding="utf-8"?>'; ?>

<user login="<?php echo $user->username ; ?>" description="<?php echo htmlentities($user->description); ?>" last_activity="<?php echo $user->last_activity ; ?>" <?php if (isset($avatar)) echo 'avatar="'.$avatar.'" '; ?> />