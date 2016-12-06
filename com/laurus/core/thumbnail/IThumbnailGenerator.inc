<?php

/**
 * This Interface defines All the CompressorTypes Required.
 * If want to add new Compressor Type Just add another Type name and assign  int value to it.
 * @author Kunal Mestri
 * 
 */
interface IThumbnailGenerator {
        const NAME="THUMBNAIL_SERVICE"; 
        const THUMB_NAIL_TYPES="THUMB_NAIL_TYPES";
        const IMAGE_JPG="image/jpg";
        const IMAGE_PNG="image/png";
        const IMAGE_GIF="image/gif";
        const IMAGE_JPEG="image/jpeg";
        const IMAGE_PJPEG="image/pjpeg";        
        public function generate($path,$type);
        public function doesNeedToBeCreate($path);
    
}

?>
