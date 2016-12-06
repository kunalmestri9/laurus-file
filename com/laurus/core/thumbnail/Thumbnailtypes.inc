<?php

class Thumbnailtypes {
    private $width;
    private $height;
    private $name;
    private $postfix;
    public function getWidth() {
        return $this->width;
    }

    public function setWidth($width) {
        $this->width = $width;
    }

    public function getHeight() {
        return $this->height;
    }

    public function setHeight($height) {
        $this->height = $height;
    }

    public function getName() {
        return $this->name;
    }

    public function setName($name) {
        $this->name = $name;
    }

    public function getPostfix() {
        return $this->postfix;
    }

    public function setPostfix($postfix) {
        $this->postfix = $postfix;
    }


}

?>
