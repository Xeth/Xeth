
var Profile = Backbone.Model.extend({

    idAttribute: "uri",

    initialize:function(){
        _(this).bindAll("setReady", "parseEvent");
        this.set("loaded", false);
        this.fetchDetails();
    },

    fetchDetails:function(){
        var future = XETH_bitprofile.getDetailsAsync(this.getURI());
        var observer = new FutureObserver(future);
        var self = this;
        observer.onFinished(function(details){
            if(details!==false){
                self.set("details", details);
            }
            self.set("loaded", true);
            future.dispose();
        });
    },

    get:function(key){
        if(key=="uri"||key=="id"||key=="context"||key=="account"||key=="details"||key=="loaded")
        {
            return Backbone.Model.prototype.get.call(this, key);
        }
        else
        {
            if(key=="ipns")
            {
                var path = XETH_bitprofile.getData({uri:this.getURI(), key:"details"})||"";
                return (path.indexOf("ipns://") > -1)
            }
            else
            {
                return XETH_bitprofile.getData({uri:this.getURI(), key:key})||"";
            }
        }
    },

    observe:function(){
        XETH_event.Data.connect(this, this.parseEvent);
    },

    parseEvent:function(event){
        if(event.context=="bitprofile"&&event.uri==this.getURI())
        {
            this.set(event.key, event.value);
        }
    },

    stopListening:function(){
        Backbone.Model.prototype.stopListening.call(this);
        XETH_event.Data.disconnect(this, this.parseEvent);
    },

    getURI:function(){
        return Backbone.Model.prototype.get.call(this, "uri");
    },

    exportKey:function(path){
        var request = {path: path, uri:this.getURI()}
        return XETH_bitprofile.exportProfile(request);
    },

    watchFuture : function(future, key, callback){
        var self = this;
        var observer = new FutureObserver(future);
        observer.onFinished(function(result){
            if(data===false){
                self.trigger("error", key);
            }else{
                self.set(key, data);
            }
            future.dispose();
            if(callback instanceof Function) callback(result);
        });

    },

    linkStealthAddress:function(request, callback){
        request.uri = this.getURI();
        this.watchFuture(XETH_bitprofile.linkStealthAddressAsync(request), "payments", callback);
    },

    changeURI:function(request, callback){
        request.uri = this.getURI();
        this.watchFuture(XETH_bitprofile.moveProfileAsync(request), "uri", callback);
    },

    changeDetails:function(request, callback){
        request.uri = this.getURI();
        this.watchFuture(XETH_bitprofile.updateDetailsAsync(request), "details", callback);
    }

});

var ProfileCollection = Backbone.Collection.extend({

    fetch:function(){
        var profiles = XETH_bitprofile.listProfiles();
        if(profiles.length){
            this.reset(profiles);
        }else{
            if(this.length){
                this.reset();
            }
        }
    },

    create:function(data){
        return XETH_bitprofile.createProfile(data);
    },
    
    importKey:function(path){
        return XETH_bitprofile.importProfile(path);
    },

    findProfile:function(uri, callback){
        var profile = this.find({uri:uri});
        if(profile) callback(profile);
    },

    exportKey:function(uri, path){
        this.findProfile(uri,function(profile){
            profile.exportKey(path);
        });
    },

    observe:function(){
        XETH_event.Profile.connect(this, this.add);
    },

    model: Profile
});
