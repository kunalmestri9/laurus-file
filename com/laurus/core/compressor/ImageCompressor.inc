<?php
import('com.laurus.core.compressor.ICompressor');
import('com.laurus.core.file.ImageFile');
import('com.laurus.core.file.IFileTypes');
class  ImageCompressor implements ICompressor {
    
    private /*String*/ $path;
    public function getCompressorType() {
        return ICompressorTypes::IMAGECOMPRESSOR;
    }
   /**
    
    * @param <? extends ImageFile> $imageobj
    */
    public function  __construct($imageobj) {
         
        if(class_implements("IFile")&& $imageobj->getFileType()==IFileTypes::IMAGE){
            $this->path=$imageobj->getFileName();
        }
        else
          throw new Exception("Parameter must be type of ImageFile");
    }
    
    public function compress(/*int*/ $percentage){
          $save = "images/" . $imagepath; //This is the new file you saving
          list($width, $height) = getimagesize($this->path) ;
          $tn = imagecreatetruecolor($width, $height) ;
          $image = imagecreatefromjpeg($file) ;
          imagecopyresampled($tn, $image, 0, 0, 0, 0, $width, $height, $width, $height) ;
          imagejpeg($tn, $save, 100) ;
          $save = "images/comp_" . $imagepath; //This is the new file you saving
          $file = "images/" . $imagepath; //This is the original file
          list($width, $height) = getimagesize($file) ;
          $modwidth = $width;
          $diff = $width / $modwidth;
          $modheight = $height;
          $tn = imagecreatetruecolor($modwidth, $modheight) ;
          $image = imagecreatefromjpeg($file) ;
          imagecopyresampled($tn, $image, 0, 0, 0, 0, $modwidth, $modheight, $width, $height) ;
          imagejpeg($tn, $save, 75) ;
    }
    
}
class ImageSize{
    private $height;
    private $width;
    public function __construct(){

        
    }
    function getImageWidth(){

    }
}
interface ImageTypes{
    const THUMB=0; //100px * 100px
    const COVER=1; //
    const HEADGALLERY=2;
    const GALLERY=3;
    const PROFILEPIC=4;
    const OTHER=999;
}

?>
