<?php
import("com.laurus.velox.services.api.IFileCheckerService");
import("com.laurus.core.connection.CoreConnection");
import("com.laurus.core.services.TQueryList");
import("com.laurus.core.collection.SimpleList");
import("com.laurus.core.collection.Map");
class MFileCheckerService implements IFileCheckerService {
    private $logger;
    private $conn;
    private $map;
    private static $instance;
    private static $SERVICE_NAME="file";
    private $allowedExtensionMap;
    public static function getInstance(){
        if(self::$instance==null){
            self::$instance=new MFileCheckerService();
        }
        return self::$instance;
    }
    public function  __construct() {
        $this->conn=new CoreConnection();
        $this->conn->setConnectionType(IConnectionType::SIMPLECONNECTION);
        $this->logger=Logger::getLogger(__CLASS__);
        $this->map=new Map();
    }    
    public function init(\IServiceConfig $config) {
        $this->allowedExtensionMap=$config->getConfigParameter(IFileCheckerService::AllowedExtensions);
        $this->logger->debug("Configure Extensions are".$this->allowedExtensionMap);
        foreach ($this->allowedExtensionMap as $key=>$value){
            $this->map->put($key, $value);
         }
           $this->logger->debug($this->map); 
           $this->logger->debug($this->map->get("DEPART_IMAGE"));
    }
    public function checkExtenstion(\ImageFile $image){
        $this->logger->debug("inside checkExtenstion");
//        $extention = array( 'png', 'jpg', 'jf' );
        $imageName=$image->getFileName();
        $imageNamePiece= explode(".", $imageName);
     
        for($i=0;$i<=5;$i++){
            $this->logger->debug(count($this->extention));
            $extention=explode(",",$this->extention);
            $this->logger->debug($extention[$i]);
           while($imageNamePiece[1]==$extention[$i]){
              $this->logger->debug($imageNamePiece);
              $this->logger->debug("You can upload your file");
              return 1;
           }
        
        }
       return null;
    }
    
    public function checkSize(){
        
    }

    public function getAllowedExtensionFor($key) {
        return (is_string($key))? $this->map->get($key) : false;
    }
   
}

?>
