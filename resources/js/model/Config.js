var Config = Backbone.Model.extend({

    get: function(name){
        return XETH_config.get(name);
    },

    getFlag: function(name){
        return parseInt(XETH_config.get(name))!=0;
    },

    setFlag:function(name, val){
        return this.set(name, val?"1":"0");
    },

    set: function(name, value){
        if(XETH_config.set({name: name, value:value}))
        {
            this.triggerChange(name, value);
            return true;
        }
        return false;
    },

    updateEthereumClient:function(path){
        return XETH_config.updateEthereumClient(path);
    },

    observe: function(){
        XETH_config.Change.connect(this, this.triggerChange);
    },

    triggerChange: function(name, value){
        this.trigger("change", this);
        this.trigger("change:"+value, this, value);
    }
});
