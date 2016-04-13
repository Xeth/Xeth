

(function ( $ ) {
    $.fn.error = function(msg){
        if(msg) $(this).closest(".section_mandatory").find("h1").attr("error",msg);
        $(this).clearvalid();
        $(this).focus(function(){$(this).noerror();}).closest(".section_mandatory").addClass("error");
    };
    $.fn.noerror = function(){
        $(this).closest(".section_mandatory").removeClass("error");
    };
    $.fn.valid = function(){
        $(this).noerror();
        $(this).closest(".section_mandatory").addClass("valid");
    };
    $.fn.clearvalid = function(){
        $(this).closest(".section_mandatory").removeClass("valid");
    };
    $.fn.validate = function(callback) {
        var result = true;
        this.each(function(){
            var input = $(this);
            if(!input.val().length){
                input.error();
                if(callback!=undefined){
                    callback(input);
                }
                result = false;
            }
			else input.noerror();
        });
        return result;
    };
 
}( jQuery ));
