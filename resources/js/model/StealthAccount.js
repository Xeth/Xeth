var StealthAccount = Backbone.Model.extend({
    idAttribute: "address",
    initialize:function(){
        this.set("balance",0);
    },

    update:function(){},
    autoUpdate:function(){},
    send:function(){
        return false;
    }
});
