var Contact = Backbone.Model.extend({

    idAttribute: "alias",

    initialize:function(data, options){
        if(options.transactions){
            _(this).bindAll("resolve");
            var total = 0;
            var address = this.get("address");
            var bitprofile = this.get("bitprofile");
            this.set("transactions", 0);
        }
    },

    save:function(){
        if(this.hasChanged("alias")){
            if(!XETH_addressbook.renameContact({previous:this.previous("alias"), alias: this.get("alias")})){
                return false;
            }
            if(Object.keys(this.changedAttributes()).length>1){
                return XETH_addressbook.editContact(this.toJSON());
            }
        }
        else{
            return XETH_addressbook.editContact(this.toJSON());
        }
        return true;
    },

    destroy:function(){
        XETH_addressbook.removeContact(this.get("alias"));
        this.trigger("destroy", this);
    },

    resolve:function(transaction){
        var address = ""+this.get("address");
        var bitprofile = ""+this.get("bitprofile");
        if((address.length && (address==transaction.get("from")||address==transaction.get("to")||address==transaction.get("stealth")))||(bitprofile.length &&bitprofile==transaction.get("bitprofile"))){
            transaction.bindContact(this);
            this.set("transactions", (this.get("transactions")||0)+1);
            return true;
        }
        return false;
    }

});

var AddressBook = Backbone.Collection.extend({

    initialize:function(models, options){
        _(this).bindAll("upsert", "resolveTransaction", "resolveNewContact");
        this.transactions = options?options.transactions:null;
    },

    fetch:function(){
        var contacts = XETH_addressbook.listContacts();
        if(contacts.length){
            this.reset(contacts);
        }else{
            if(this.length){
                this.reset();
            }
        }
    },

    create:function(data){
        var model = this.model(data);
        if(!XETH_addressbook.addContact(model.toJSON())) return false;
//        this.add(model);
        return true;
    },

    resolve:function(transactions){
        for(var j in transactions.models)
        {
            this.resolveTransaction(transactions.models[j]);
        }
        this.transactions = transactions;
        this.transactions.on("add", this.resolveTransaction);
        this.on("add", this.resolveNewContact);
    },

    resolveTransaction:function(transaction){
        for(var i in this.models)
        {
            if(this.models[i].resolve(transaction))
            {
                return true;
            }
        }
        return false;
    },

    resolveNewContact:function(contact){
        for(var j in this.transactions.models)
        {
            var transaction = this.transactions.models[j];
            contact.resolve(transaction);
        }
    },

    upsert:function(data){
        var old = this.get(data.alias);
        if(old)
        {
            for(var i in data)
            {
                old.set(i, data[i]);
            }
        }
        else
        {
            this.add(data);
        }
    },

    observe:function(){
        XETH_addressbook.Contact.connect(this, this.upsert);
    },

    model: function(data, options){
        return new Contact(data, {transactions:this.transactions});
    }

});
