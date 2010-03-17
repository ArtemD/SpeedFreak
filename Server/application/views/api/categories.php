<?php echo "<?"; ?>xml version="1.0" encoding="utf-8" <?php echo "?>"; ?>

<categories>
    <?php foreach ($categories as $k){ ?>   <category description="<?php echo $k->description; ?>" unit="<?php echo $k->unit; ?>"><?php echo $k->slug; ?></category>
<?php } ?></catgories>