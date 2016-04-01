var Profile = Backbone.Model.extend({

    idAttribute: "uri",

    initialize:function(data, options){
    },

    save:function(){
        
    },
    
    export:function(){},

    destroy:function(){
        this.trigger("destroy", this);
    },
    
    linkStealthAddress:function(address,callback){
        
    }

});

var ProfileCollection = Backbone.Collection.extend({

    initialize:function(models, options){

    },

    fetch:function(){
    },

    create:function(data,callback){
        var model = this.model(data);
        if(!model.save()) return false;
        this.add(model);
        return true;
    },
    
    importKey:function(){},
   
    observe:function(){
        
    },

    model: Profile
    
});
