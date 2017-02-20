<?php
import('com.laurus.core.thumbnail.IThumbnailGenerator');
import('com.laurus.core.thumbnail.IThumbnailGenerator');
import('com.laurus.core.thumbnail.Thumbnailtypes');
import("com.laurus.core.services.IService");
import("com.laurus.core.collection.SimpleList");
class  ImageThumbnailGenerator implements IThumbnailGenerator,IService {
    private static $instance;
    private $logger;
     /*@var $thumbNailList SimpleList*/
    private $thumbNailList;
    public static function getInstance() {
        if (self::$instance == null) {
            self::$instance = new ImageThumbnailGenerator();
        }
        return self::$instance;
    }
    public function init(IServiceConfig $config){
       //$this->logger->debug($config); 
       $this->thumbnailTypes=$config->getConfigParameter(IThumbnailGenerator::THUMB_NAIL_TYPES);
       $this->logger->debug($this->thumbnailTypes);
       
       
        for($i=0; $i<count($this->thumbnailTypes);$i++){
            $thumbNailType=new Thumbnailtypes();
            $this->logger->debug("===================");
            $this->logger->debug($this->thumbnailTypes[$i]);
            $this->logger->debug("===================");
            $thumbNailType->setWidth($this->thumbnailTypes[$i]["width"]);
            $thumbNailType->setHeight($this->thumbnailTypes[$i]["height"]);
            $thumbNailType->setPostfix($this->thumbnailTypes[$i]["path"]);
            $thumbNailType->setName($this->thumbnailTypes[$i]["name"]);
            $this->thumbNailList->add($thumbNailType);
            
        }
        
    }
    public function  __construct() {
         $this->thumbNailList=new SimpleList();
        $this->logger = Logger::getLogger(__CLASS__);
         $this->imagejpg=IThumbnailGenerator::IMAGE_JPG;
        $this->imagepng=IThumbnailGenerator::IMAGE_PNG;
        $this->imagegif=IThumbnailGenerator::IMAGE_GIF;
        $this->imagejpeg=IThumbnailGenerator::IMAGE_JPEG;
        $this->imagepjpeg=IThumbnailGenerator::IMAGE_PJPEG;

    }
    public function generate($path,$type){
        $this->logger->debug($this->thumbNailList);
        for($i=0;$i<$this->thumbNailList->size();$i++){
            $thumbNailType=$this->thumbNailList->get($i);
           //$this->logger->debug($this->thumbNailList);
            $this->logger->debug($this->thumbNailList->get($i));
            list($width, $height) = getimagesize($path) ; //get width & height in array list
            $tn = imagecreatetruecolor($thumbNailType->getWidth(), $thumbNailType->getHeight()); 
            if(!strcmp($this->imagepng,$type)){
                imagealphablending($tn, false); //For transparent BackGround
                imagesavealpha($tn, true);  
            }
            if(!strcmp($this->imagejpg,$type) || !strcmp($this->imagejpeg,$type) || !strcmp( $this->imagepjpeg,$type))
                 $src_img=imagecreatefromjpeg($path);
            if(!strcmp($this->imagepng,$type))
                 $src_img=imagecreatefrompng($path);
            if(!strcmp($this->imagegif,$type))
                 $src_img=imagecreatefromgif($path);

           imagecopyresampled($tn, $src_img, 0, 0, 0, 0, $thumbNailType->getWidth(), $thumbNailType->getHeight(), $width, $height) ; 
           $fE=$this->getFileExtension($path);
           $newFileName=$fE["filename"].$thumbNailType->getPostfix().".".$fE["ext"];
           $fullPathArr=explode(DIRECTORY_SEPARATOR,$path);
           $fullPathArr[count($fullPathArr)-1]=$newFileName;
           $newServerPath=implode(DIRECTORY_SEPARATOR, $fullPathArr);
           $this->logger->debug($newServerPath);
           if(!strcmp($this->imagepng,$type)){
           imagesavealpha($src_img, true);
           $ok=imagepng($tn,$newServerPath);
           }
           else if(!strcmp($this->imagegif,$type)){
           $ok=imagegif($tn,$newServerPath);
           }
           else{
           $ok=imagejpeg($tn,$newServerPath);
           }
         }
      }
      
    public function generateDynamic($image,$type,$l) {
        $this->logger->debug(__METHOD__);

        $arr=explode("-", $l);
        if(TUtilString::equals("h",$arr[0])){
            $this->logger->debug("IN");

            $height=$arr[1];
            $image_properties = getimagesize($image);
            $image_width = $image_properties[0];
            $image_height = $image_properties[1];
            $image_ratio = $image_width / $image_height;
            $type = $image_properties["mime"];
            $width = round($height * $image_ratio);
            if($type == "image/jpeg") {
                    header('Content-type: image/jpeg');
                    $thumb = imagecreatefromjpeg($image);
            } elseif($type == "image/png") {
                    header('Content-type: image/png');
                    $thumb = imagecreatefrompng($image);
            } else {
                    return false;
            }



	    /*if($type == "image/jpeg") {
                    $ok=imagejpeg($thumb);
            } else {
                    $ok=imagepng($thumb);
            }
            $this->logger->debug("Is Email Generated " . $ok);

            //imagedestroy($temp_image);
            //imagedestroy($thumbnail);
            return;

            */





            
            //if($type == "image/png"){
               // $temp_image = imagecreate($width, $height);
           // }else{
                $temp_image = imagecreatetruecolor($width, $height);
           // }



             if($type=="image/png"){
		$background = imagecolorallocate($temp_image , 0, 0, 0);
		 // removing the black from the placeholder
        	imagecolortransparent($temp_image, $background);
		imagealphablending($temp_image, false);
	        imagesavealpha($temp_image, true);


	     }
            //$temp_image = imagecreatetruecolor($width, $height);
            imagecopyresampled($temp_image, $thumb, 0, 0, 0, 0, $width, $height, $image_width, $image_height);
           //if($type == "image/png"){
               $thumbnail = imagecreate($width, $height);
           //}else{
           //     $thumbnail = imagecreatetruecolor($width, $height);
           // }
           
            header( 'Cache-Control: max-age=604800' );
            header('Expires: '.date(DATE_RFC1123,time()+2592000));


           if($type == "image/jpeg") {
                    $ok=imagejpeg($temp_image);
            } else {
                    $ok=imagepng($temp_image);
            }
            $this->logger->debug("Is Email Generated " . $ok);

            imagedestroy($temp_image);
            imagedestroy($thumbnail);
            return;
/*
            


            
            //imagealphablending($thumbnail, true);
            if($type == "image/png"){

	    	imagesavealpha($thumbnail,true);
            	$color = imagecolorallocatealpha($thumbnail, 255, 255, 255, 127);
                imagefill($thumbnail, 0, 0, $color);
                imagecolortransparent($thumbnail, $color);
	   }
//imagealphablending($thumbnail, true);
            
            
            imagecopyresampled($thumbnail, $temp_image, 0, 0, 0, 0, $width, $height, $width, $height);
            
            
            
 //           header( 'Cache-Control: max-age=604800' );
 //           header('Expires: '.date(DATE_RFC1123,time()+2592000));
            if($type == "image/jpeg") {
                    $ok=imagejpeg($thumbnail);
            } else {
                    $ok=imagepng($thumbnail);
            }
            $this->logger->debug("Is Email Generated " . $ok);
            
            imagedestroy($temp_image);
            imagedestroy($thumbnail);
*/
        }
    }
       
  private function getFileExtension($fileName) {
        if($fileName!=NULL){
            $path= pathinfo($fileName);
            if($path['filename']!=null){
                return array(
                    "filename"=> $path['filename'],
                    "ext"=> $path['extension']
                );
                    
            }else{
                $this->logger->error("Required File name");
                throw new ValidationException("Required File name");
            }
        }
    }

    public function doesNeedToBeCreate($path) {
        for($i=0;$i<$this->thumbNailList->size();$i++){
            /* @var $thumbNail Thumbnailtypes */
            $thumbNail=$this->thumbNailList->get($i);
            if(!file_exists($this->str_lreplace(".", $thumbNail->getPostfix().".", $path))){
                return true;
            }
        }
        return false;
    }    
    
    private function str_lreplace($search, $replace, $subject){
        $pos = strrpos($subject, $search);
        if($pos !== false){
            $subject = substr_replace($subject, $replace, $pos, strlen($search));
        }
        return $subject;
    }
    
}
?>
